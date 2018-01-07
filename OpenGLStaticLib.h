#define POSITION_SIZE 3
#define COLOR_SIZE 4

class OpenGLStaticLib{
    
    private:
    
    int position_pos = 0;
    int color_pos = 0;
    
    
    public:
    
    void setPositionPos(int pos){
        position_pos = pos;
    }
    
    void setColorPos(int pos){
        color_pos = pos;
    }
    
    void deleteBuffer(int *VBO, bool isCompact){
        if(isCompact){
            glDeleteBuffer(2, VBO);
        }else{
            glDeleteBuffer(3, VBO);
        }
    }
    
    //use this method if the vertex attributes are stored in a single buffer
    // number of vertices, client buffer, stride between elements, number of indices, index buffer
    void Draw_VBO_Compact(GLuint vertex_num, GLfloat *buffer, GLuint stride, GLuint index_num, GLushort *indices, int *VBO){
        GLuint bufferOffset = 0;
        //VBO has two elements, each one of which is a buffer.
        if(VBO[0] == 0 && VBO[1] == 0){
            glGenBuffers(2, VBO);
            
            glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
            glBufferData(GL_ARRAY_BUFFER, stride * vertex_num, buffer, GL_STATIC_DRAW); //stride is the size of each vertex attribute element
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]); //for indices
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * index_num, indices, GL_STATIC_DRAW);
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[1]);
        
        //the position and color vectors are not constant in this case
        glEnableVertexAttribArray(position_pos);
        glEnableVertexAttribArray(color_pos);
        
        //processing the position vectors: assume that the position vectors are put before the color vectors
        glVertexAttribPointer(position_pos, POSITION_SIZE, GL_FLOAT, GL_FALSE, stride, (const void*)bufferOffset);
        offset += POSITION_SIZE * sizeof(GLfloat);
        glVertexAttribPointer(color_pos, COLOR_SIZE, GL_FLOAT, GL_FALSE, stride, (const void*)bufferOffset);
        
        glDrawElements(GL_TRIANGLES, index_num, GL_UNSIGNED_SHORT, 0);
        
        glDisableVertexAttribArray(position_pos);
        glDisableVertexAttribArray(color_pos);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    
    //here we treat buffer as a two-dimensional array, and strides an array
    void Draw_VBO_Separate(GLuint vertex_num, GLfloat **buffer, GLuint *strides, GLuint index_num, GLushort* indices, int *VBO){
        if(VBO[0] == 0 && VBO[1] == 0 && VBO[2] == 0){
            glGenBuffers(3, VBO);
            
            glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
            glBufferData(GL_ARRAY_BUFFER, strides[0] * vertex_num, buffer[0], GL_STATIC_DRAW);
            
            glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
            glBufferData(GL_ARRAY_BUFFER, strides[1] * vertex_num, buffer[1], GL_STATIC_DRAW);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[2]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * index_num, buffer[2], GL_STATIC_DRAW);
        }
        
        //here we treat VBO as a two dimensional array for its first two elements
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glEnableVertexAttribArray(position_pos);
        glVertexArrayAttribPointer(posiiton_pos, POSITION_SIZE, GL_FLOAT, GL_FALSE, strides[0], 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glEnableVertexAttribArray(color_pos);
        glVertexArrayAttribPointer(color_pos, COLOR_SIZE, GL_FLOAT, GL_FALSE, strides[1], 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER);
        glDrawElements(GL_TRIANGLES, index_num, GL_UNSIGNED_SHORT, 0);
        
        glDisableVertexAttribArray(position_pos);
        glDisableVertexAttribArray(color_pos);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
