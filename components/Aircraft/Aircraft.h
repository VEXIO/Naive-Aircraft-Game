//
// Created by Haotian on 17/5/30.
//

#ifndef MEGAPROJECT_AIRCRAFT_H
#define MEGAPROJECT_AIRCRAFT_H

#include "../../libs/myGL.h"
#include "../SkyBox/SkyBox.h"
#include "../AABB/AABB.h"

#include <iostream>

using namespace std;

const glm::vec3 X = glm::vec3(1.0f, 0.f, 0.f);
const glm::vec3 Y = glm::vec3(0.0f, 1.f, 0.f);
const glm::vec3 Z = glm::vec3(0.0f, 0.f, 1.f);

const GLuint DEPTH_TEXTURE_SIZE = 2048;

class Aircraft {
public:
    Aircraft(glm::mat4 &, glm::mat4 &, glm::vec3 &);

    ~Aircraft();

    void loadIdentity() { setCameraCoordinate(); }

    void setupShaders(const char *vertBodyFile, const char *fragBodyFile, const char *vertShadowFile,
                      const char *fragShadowFile);

    void setupSkyBox(const char *skyShadervs, const char *skyShaderfs);

    void setupBuffers(const char *objPath, const char *objFile);

    void processNormalKeys(unsigned char key, int x, int y);

    void processMouseMotion(int xpos, int ypos);

    void processMouseAction(int button, int state, int x, int y);

    void changeSize(int w, int h);

    void render();

    void motion();

    void idle();

    bool isCollided(AABB *a);

protected:
    void updateMVP();

    void setBodyUniforms();

    void setCameraCoordinate();

private:
    GLuint pb, vb, fb, shadowProgram, shadowVert, shadowFrag;

    //mouse motion
    bool firstPerson = false;
    glm::vec3 lastPosition;
    glm::vec3 dir;
    bool stopCameraTracing = false;
    bool resetPos = true;
    double lastX, lastY, Pitch = 0, Yaw = 90;
    //end of mousemotion

    //sky box
    GLuint skyShader;
    GLuint cubemapTexture;
    GLuint skyboxVAO, skyboxVBO;
    //end of sky box

    struct {
        GLint vertexLoc, normalLoc;
        GLint ModelMatrixLoc, ViewMatrixLoc, ProjectionMatrixLoc, MVPMatrixLoc;
        GLint KaLoc, KdLoc, KsLoc;
        GLint idLoc;
        GLint AmbientLoc, LightColorLoc, LightDirectionLoc, HalfVectorLoc, ShininessLoc, StrengthLoc;
    } BodyUniformLoc, ShadowUniformLoc;

    glm::vec3 Ambient = glm::vec3(0.4f), LightColor = glm::vec3(1.0f), LightDirection, HalfVector;
    GLfloat Shininess = 1.f, Strength = 5.0f;

    GLuint vao[3];

    AABB aabb;

    GLfloat WinRatio;

    GLuint depth_texture, depth_fbo;

    GLint winW, winH;

    glm::vec3 viewDirVect = glm::vec3(0.0f, 0.37f, -1.2f), lookAtVect = Y;

    glm::vec3 cameraFront = Z;

    glm::mat4 modelMatObj = glm::mat4(1.f),
            &viewMatObj, &projMatObj, MVPMatObj, shadowMVPMatObj;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.

    std::vector<MyGLMaterial> materials;
    std::vector<int> material_mapper;
    std::vector<GLfloat> material_ids;

    glm::vec3 currentPos = glm::vec3(0.f), upVector = Z;

    const GLfloat planeWeight = 1;
    GLfloat engineForce = 9.80f;

    glm::vec3 planeAcceleration;
    glm::vec3 planeVelocity;
    glm::vec3 pullForce;
    glm::vec3 airFriction;
    glm::vec3 gravityForce = glm::vec3(0, 0, -9.8f);

    GLfloat airFricConst = -0.00001f;

    glm::vec3 &cameraLocation;

    GLfloat rotateLR = 0.f, rotateUD = 0.f, rotateQE = 0.f;

    GLfloat scale = .5f;

    const glm::mat4 scaleBiasMatrix = glm::mat4(glm::vec4(0.5f, 0.0f, 0.0f, 0.0f),
                                                glm::vec4(0.0f, 0.5f, 0.0f, 0.0f),
                                                glm::vec4(0.0f, 0.0f, 0.5f, 0.0f),
                                                glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

    GLfloat polar_r = 2000;
};

#endif //MEGAPROJECT_AIRCRAFT_H
