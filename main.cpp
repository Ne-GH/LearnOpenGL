#include <glad/glad.h>  // 必须为首句
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>
#include <cmath>

#include "stb_image.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // 初始化FLFW
    glfwInit();
    // 使用OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 使用的是核心模式(Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);
    if (window == nullptr) {
        std::cerr << "创建GLFW窗口失败" << std::endl;
        glfwTerminate();
        return -1;
    }
      // 设置为当前线程的主上下文
    glfwMakeContextCurrent(window);

    // 使用GLAD管理OPENGL的函数指针
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourShader("./vertex_shader.vs","./fragment_shader.fs");



    // 标准化设备坐标，屏幕中心为原点
    // 上为y轴正方向, 右为x轴正方
//    float vertices[] = {
//            // positions          // colors           // texture coords
//            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
//    };
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int indices[] = {
//            0 ,1 ,3,
//            1 ,2 ,3
    };

    // 定点缓冲对象,（其值是定点缓冲对象独一无二的ID）
    unsigned int VBO,VAO,EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    // 数据几乎不会改变
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    // 位置属性
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float ),(void*)0);
    glEnableVertexAttribArray(0);

    // 颜色属性
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(float ),(void*)(3*sizeof(float )));
    glEnableVertexAttribArray(1);

    // 贴图
//    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float ),(void*)(6*sizeof(float )));
//    glEnableVertexAttribArray(2);

    // 加载并创建质地（贴图）
    unsigned int texture;
    // 参数1 是生成的纹理数量
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);

    // 设置纹理环绕
    // 纹理目标，设置的选项，应用的纹理轴
    // 2d,wrap选项，S轴
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    // 2d,wrap选项，T轴
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    // 纹理过滤
    // 缩小的时候使用临近过滤
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    // 放大的时候使用线性过滤
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    // nrChannels是颜色通道个数
    int width,height,nrChannels;
    unsigned char *data = stbi_load("./resources/container.jpg",&width,&height,&nrChannels,0);
    if (data) {
        // 当调用glTexImage2D时，当前绑定的纹理对象就会被附加上纹理图像
        // 参数1：贴图目标：2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理，绑定到1D和3D的纹理不受影响
        // 参数2：多级渐远纹理的级别，0为基本级别
        // 参数3：纹理储存为GRB格式
        // 参数4，5：宽，高
        // 总为0,（历史遗留）
        // 参数7,8：原图的格式和数据类型
        // 存储到data
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "filed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture 2
    unsigned int texture2;
    glGenTextures(1,&texture2);
    glBindTexture(GL_TEXTURE_2D,texture2);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    // 反转图片
    // 否则是颠倒的，因为OpenGL要求y轴的0在图片的底部，但是图片y轴的0在顶部
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("./resources/awesomeface.png",&width,&height,&nrChannels,0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();// 在设置uniform变量之前激活着色器
    glUniform1i(glGetUniformLocation(ourShader.ID,"texture1"),0); // 手动设置
    ourShader.SetInt("texture2",1); // 或者使用着色器类设置


    // 视口
    // 前两个参数是左下角坐标，后面是宽高
    glViewport(0,0,800,600);
    // 注册事件，窗口大小调整的时候调用这个函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 开启深度测试
    glEnable(GL_DEPTH_TEST);


    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // 投影矩阵
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),(float)SCR_WIDTH / (float)SCR_HEIGHT,1.0f,100.0f);
    ourShader.SetMat4("projection",projection);

    // 摄像机
    glm::vec3 cameraPos = glm::vec3(0.0f,0.0f,3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f,0.0f,-1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f,1.0f,0.0f);


    // 窗口是否要求退出
    while (!glfwWindowShouldClose(window)) {

        // 输入
        processInput(window);

        glClearColor(0.2f, 0.3f, 1.2f, 1.0f);// 设置清空缓冲（屏幕）所用的颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// 清空颜色缓冲并在每次渲染迭代之前清除深度缓冲（否则前一帧的深度信息仍然保存在缓冲中）

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,texture2);

        ourShader.use();
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos,cameraPos + cameraFront,cameraUp);
        ourShader.SetMat4("view",view);

        float cameraSpeed = 0.05f;
        if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
            cameraPos += cameraSpeed * cameraFront;
        }
        if (glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS) {
            cameraPos -= cameraSpeed * cameraFront;
        }
        if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS) {
            cameraPos -= glm::normalize(glm::cross(cameraFront,cameraUp) * cameraSpeed);
        }
        if (glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS) {
            cameraPos += glm::normalize(glm::cross(cameraFront,cameraUp) * cameraSpeed);
        }


        for (int i = 0;i < 10; ++i) {

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            float angle = 20.0f * i;
            model = glm::rotate(model,glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));
            ourShader.SetMat4("model",model);

            glDrawArrays(GL_TRIANGLES,0,36);
        }


        // 触发事件
        glfwPollEvents();
        // 交换缓冲区颜色
        glfwSwapBuffers(window);
    }

    // 释放删除之前分配的资源
    glfwTerminate();


    return 0;
}
