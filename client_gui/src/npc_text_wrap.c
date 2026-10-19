#include "npc.h"

static void	get_next_word(const char **text, char *word, size_t size)
{
	size_t	i;

	while (**text == ' ')
		(*text)++;
	i = 0;
	while (**text && **text != ' ' && i < size - 1)
	{
		word[i++] = **text;
		(*text)++;
	}
	word[i] = '\0';
}

static int	draw_wrapped_word(t_text_wrap *wrap, const char *word)
{
	float	width;
	float	space_width;

	width = MeasureText(word, wrap->font_size);
	space_width = MeasureText(" ", wrap->font_size);
	if (wrap->x != wrap->bounds.x
		&& wrap->x + width > wrap->bounds.x + wrap->bounds.width)
	{
		wrap->x = wrap->bounds.x;
		wrap->y += wrap->font_size + 4;
	}
	if (wrap->y + wrap->font_size
		> wrap->bounds.y + wrap->bounds.height)
		return (0);
	DrawText(word, wrap->x, wrap->y, wrap->font_size, wrap->color);
	wrap->x += width + space_width;
	return (1);
}

void	draw_text_wrapped(const char *text, Rectangle bounds,
		int font_size, Color color)
{
	t_text_wrap	wrap;
	char		word[128];

	if (!text)
		return ;
	wrap = (t_text_wrap){
		.bounds = bounds,
		.font_size = font_size,
		.color = color,
		.x = bounds.x,
		.y = bounds.y
	};
	while (*text)
	{
		get_next_word(&text, word, sizeof(word));
		if (word[0] == '\0')
			break ;
		if (!draw_wrapped_word(&wrap, word))
			break ;
	}
}
