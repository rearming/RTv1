#ifndef RTV1_DEFINES_H
# define RTV1_DEFINES_H

# define RTV1_DEBUG 0

# define MOVE_SPEED 0.2
# define SIDE_MOVE_SPEED 0.1
# define FLY_SPEED 0.2

# define ROTATION_SPEED 0.05

# define M_PI_180 (M_PI / 180)

# define NOT_SET (-1)
# define TRUE 1
# define FALSE 0

# define WIN_TITLE "Dota 4"

# define WIN_WIDTH 2000
# define WIN_HEIGHT 1000
# define WIN_RATIO ((float)WIN_WIDTH / WIN_HEIGHT)
# define INVERSE_RATIO ((float)WIN_HEIGHT / WIN_WIDTH)
# define D_E_KARMATSKIY (INVERSE_RATIO * INVERSE_RATIO)
# define D_I_MAZOHIN (WIN_RATIO * WIN_RATIO)
# define SCALE_WIDTH 1
# define SCALE_HEIGHT 1

# define COL_NOT_SET (-1)
# define COL_RED 0xFF0000
# define COL_GREEN 0x00FF00
# define COL_BLUE 0x0000FF
# define COL_YELLOW 0xFFFF00
# define COL_WHITE 0xFFFFFF
# define COL_GREY 0x3A3635
# define COL_BLACK 0x0
# define COL_PURPLE 0x7830E0
# define COL_MAGNETA 0xE2007A

# define COL_BG COL_GREY

# define MATERIAL_OPAQUE -1

# define STR_SPHERE "sphere"
# define STR_PLANE "plane"
# define STR_CYLINDER "cylinder"
# define STR_CONE "cone"

# define STR_LIGHT "light"
# define STR_POINT_LIGHT "point"
# define STR_DIRECTIONAL_LIGHT "directional"
# define STR_AMBIET_LIGHT "ambient"

# define STR_CENTER "center("
# define STR_POS "pos("
# define STR_ROTATION "rotation("
# define STR_NORMAL "normal("
# define STR_ANGLE "angle("
# define STR_LENGTH "length("
# define STR_RADIUS "radius("
# define STR_COLOR "color("
# define STR_SPECULAR "specular("

# define EXIT_SUCCESS 0

#endif
