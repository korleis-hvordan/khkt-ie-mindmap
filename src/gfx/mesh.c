#include "mesh.h"
#include "../state.h"

void mesh_render(Mesh *self) {
	mat4s model = glms_translate(glms_mat4_identity(), self->position);
	shader_uniform_mat4(self->material->shader, "m", glms_rotate(model, glfwGetTime(), (vec3s){ { 0.0f, 1.0f, 0.0f } }));

	BaseMeshBuffer *indices = mesh_get_mesh_buffer(self, self->data.length - 1);
	bo_bind(&indices->bo);
	vao_bind(&self->vao);
	shader_bind(self->material->shader);
	glDrawElements(GL_TRIANGLES, indices->data.length, indices->gl_type, 0);
}

void mesh_destroy(Mesh *self) {
	vao_destroy(&self->vao);
	for (u32 i = 0; i < self->data.length; i++) {
		bo_destroy(&mesh_get_mesh_buffer(self, i)->bo);
	}
	free(self->data.raw);
}