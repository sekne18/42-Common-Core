CC := cc
CFLAGS = -Wall -Wextra -Werror -Wuninitialized
DEBUGFLAGS = -g #-fsanitize=address
OS := $(shell uname)

LIBS := libft

SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj

INC_FLAGS = -I$(INC_DIR) $(addprefix -I, $(addsuffix /include, $(LIBS))) $(addprefix -I, $(MLX_DIR))

ifeq ($(OS), Darwin)
	MLX_DIR := minilibx_opengl_20191021
	LINK_FLAGS := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit $(addprefix -L, $(LIBS))  $(subst lib,-l,$(LIBS))
	DEF += -D__DARWIN__
else ifeq ($(OS), Linux)
	MLX_DIR := minilibx-linux
	LINK_FLAGS := -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lX11 -lXext -lm -lbsd $(addprefix -L, $(LIBS)) $(subst lib,-l,$(LIBS))
	DEF += -D__LINUX__
else
	$(error OS="$(OS)" not supported)
endif

#$(addprefix $(OS), cleanup.c)
FILES := main.c conversions.c lerp.c \
scene_loader/save_render.c scene_loader/load_scene.c scene_loader/load_obj.c \
scene_loader/load_texture.c \
scene_loader/parsing/parser.c scene_loader/parsing/executor.c scene_loader/parsing/create_materials.c \
scene_loader/parsing/utils.c scene_loader/parsing/digit_utils.c scene_loader/parsing/build_objects.c \
scene_loader/parsing/validators.c scene_loader/parsing/obj_validators.c scene_loader/parsing/vector_utils.c \
scene_loader/parsing/material_utils.c scene_loader/parsing/obj_validators2.c scene_loader/parsing/build_objects2.c \
scene_loader/parsing/obj_count.c scene_loader/parsing/create_inits.c scene_loader/parsing/obj_utils.c \
scene_loader/create_textures.c \
window/render.c window/img_utils.c window/key_hook.c \
scene_manager/new_scene.c scene_manager/material.c scene_manager/create_object.c \
scene_manager/bvh.c scene_manager/bbox.c scene_manager/bvh_utils.c scene_manager/mesh_bvh.c \
scene_manager/create_mesh.c scene_manager/create_mesh_utils.c scene_manager/create_object_2.c \
scene_manager/mesh_bvh_utils.c scene_manager/bbox_utils.c scene_manager/bbox_primitives.c \
scene_manager/add_children_mesh.c scene_manager/add_children_mesh_utils.c scene_manager/mesh_bvh_utils2.c \
scene_manager/bvh_init.c scene_manager/add_children.c \
raytracer/hit_primitives_1.c raytracer/hit_cylinder.c raytracer/fill_record_2.c raytracer/trace_bounces.c raytracer/calc_ray.c \
raytracer/raytrace.c raytracer/camera_init.c raytracer/hit.c raytracer/random.c raytracer/color_operations.c raytracer/color_conversions.c \
raytracer/fill_record.c \
raytracer/jitter.c raytracer/bvh_traverse.c raytracer/texture.c raytracer/calc_uv.c raytracer/bump_mapping_sphere.c \
raytracer/hit_bbox.c raytracer/camera_rotations.c raytracer/camera_translations.c raytracer/camera_manipulation.c \
vector/new_vector.c vector/basic_ops.c vector/basic_ops_local.c vector/basic_ops_scaled.c vector/geometry_ops.c \
vector/scalar_ops.c vector/scalar_ops_local.c vector/normalize.c vector/quaternions.c vector/limits.c \
vector/basic_ops_scaled2.c \
window/draw_bvh.c
SRCS := $(addprefix $(SRC_DIR)/, $(FILES))
OBJS := $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
NAME := miniRT

all: $(NAME)

debug: CFLAGS += $(DEBUGFLAGS)
debug: clean_self all

$(NAME): mlx $(LIBS) $(OBJS)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(DEF) -o $@ $(OBJS) $(LINK_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(DEF) -c $< -o $@

mlx:
	make -C $(MLX_DIR)

$(LIBS):
	make -C $@

clean_self:
	rm -rf $(OBJ_DIR)

clean_libs:
	make clean -C $(MLX_DIR)
	@for lib in $(LIBS); do \
		echo "make clean -C $$lib"; \
		make clean -C $$lib; \
	done

fclean_self: clean_self
	rm -f $(NAME)

fclean_libs:
	make clean -C $(MLX_DIR)
	@for lib in $(LIBS); do \
		echo "make fclean -C $$lib"; \
		make fclean -C $$lib; \
	done

clean: clean_self clean_libs

fclean: fclean_self fclean_libs

re: fclean_self all

relibs: fclean all

.PHONY: all clean fclean re relibs $(LIBS) mlx fclean_self clean_self clean_libs debug
