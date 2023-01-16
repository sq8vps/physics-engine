#pragma once

#include <GL/gl.h>
#include "../common.hpp"
#include <vector>
#include "../vec.hpp"

namespace Graphics
{   
    /**
     * @brief A base class for all graphical shapes 
    **/
    class Shape
    {
    public:
        /**
         * @brief Set object position
         * @param pos New position
        **/
        void setPosition(Vec3 pos)
        {
            this->pos = pos;
        }
        /**
         * @brief Rotate object
         * @param angle Angle in rad
         * @param axis Rotation axis
        **/
        void rotate(float angle, Vec3 axis)
        {
            rot = RAD2DEG(angle);
            this->rotAxis = rot;
        }

        friend class Graphics;


    protected:
        std::vector<float> vertices, normals, colors; //vertices, normals and colors array for OpenGL
        std::vector<GLuint> indices; //indices array
        Vec3 pos{}; //current object position
        float rot{0.f}; //object rotation in degrees
        Vec3 rotAxis{0.f, 1.f, 0.f}; //rotation axis (set to initially rotate around Y)

    private:
        /**
         * @brief Draw object
         * @warning Should be called only by the graphics engine
        **/
        void draw()
        {
            if(vertices.size() < 3) //return if this object is not initialized (less than 1 point)
                return;

            glEnableClientState(GL_NORMAL_ARRAY); //enable arrays
            glEnableClientState(GL_COLOR_ARRAY);
            glEnableClientState(GL_VERTEX_ARRAY);

            glNormalPointer(GL_FLOAT, 0, normals.data()); //set pointers to vertices, normals and colors arrays
            glColorPointer(3, GL_FLOAT, 0, colors.data());
            glVertexPointer(3, GL_FLOAT, 0, vertices.data());

            glPushMatrix(); //push unmodified matrix
            glTranslatef(pos.x, pos.y, pos.z); //set position
            glRotatef(rot, rotAxis.x, rotAxis.y, rotAxis.z); //rotate

            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, static_cast<GLvoid*>(indices.data()));

            glPopMatrix(); //pop unmodified matrix

            glDisableClientState(GL_VERTEX_ARRAY);  //disable arrays
            glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_NORMAL_ARRAY);
            
        }
    };
};