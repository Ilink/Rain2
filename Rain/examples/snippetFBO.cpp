GLuint fbo = 0;
GLuint colorTexture = 0; // color texture for color attachment
GLuint depthRBO = 0; // render buffer object for depth buffer

// set up color texture 
// generate a texture id
glGenTextures(1, &colorTexture);
// bind the texture
glBindTexture(GL_TEXTURE_2D, colorTexture);
// set texture parameters
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
// create the texture in the GPU
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA , inScreenWidth, inScreenHeight, // need screen dimension
    0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
// unbind the texture
glBindTexture(GL_TEXTURE_2D, 0);

// create a render buffer object for the depth buffer
glGenRenderbuffers(1, &depthRBO);
// bind the texture
glBindRenderbuffer(GL_RENDERBUFFER, depthRBO);
// create the render buffer in the GPU
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, inScreenWidth, inScreenHeight);
// unbind the render buffer
glBindRenderbuffer(GL_RENDERBUFFER, 0);

// create a frame buffer object
glGenFramebuffers(1, &outFrameBufferObj);
glBindFramebuffer(GL_FRAMEBUFFER, outFrameBufferObj);
// attach the color texture to the frame buffer
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
// attach depth buffer
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRBO);

// check the frame buffer
GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
if ( status != GL_FRAMEBUFFER_COMPLETE)
{
    printf("Frame buffer cannot be generated! Status: %i\n", status);
}

glBindFramebuffer(GL_FRAMEBUFFER,0);