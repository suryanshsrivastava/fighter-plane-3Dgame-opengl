#include "sea.h"
#include "main.h"

Sea::Sea(float x, float y, float z, float width, float length, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->width = width;
    this->length = length;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        width, 0.0f, length,
       -width, 0.0f, -length,
        width, 0.0f, -length,

       -width, 0.0f, length,
        width, 0.0f, length,
       -width, 0.0f, -length, 
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Sea::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

// bool Platform::detect_collision(Player Player) {

//     return std::fabs(this->position.y - Player.position.y + 0.09f) < (Player.headradius + this->height/2) && std::fabs(this->position.x - Player.position.x - 0.1f) < (Player.headradius + this->width/2);
//     // 0.09f is an error term to stop the ball from continously bouncing

// }

// bounding_box_t Platform::bounding_box() {
//     float x = this->position.x, y = this->position.y;
//     bounding_box_t bbox = { x, y, this->width, this->height };
//     return bbox;
// }