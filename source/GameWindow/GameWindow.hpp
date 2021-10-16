/// GameWindow class, this class acts like a framework for the user to initialize a windows easily
/// and write de logic of the program at the same time
/// An use of example for an instanced class is
/// window.initWindow()
/// while(windowShouldClose()){
///  window.config_init()
/// **write the logic**
/// }
/// window.finishWindow()
/// 


#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numbers>
#include <ciso646>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_glfw.h>
#include <Time/Timer.hpp>
#include <functional>

namespace Sincronia {


	class GameWindow {

    public:


        GLFWwindow* m_window;

        /// <summary>
        /// This method initializes and launches a window using OpenGl and ImGui
        /// </summary>
        /// <returns>an integer indicating the succes of the initialization</returns>
        int initWindow() {

            // glfw: initialize and configure
        // ------------------------------
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
            #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE); // uncomment this statement to fix compilation on OS X
            #endif

            // Creating a glfw window
            constexpr unsigned int SCR_WIDTH = 600;
            constexpr unsigned int SCR_HEIGHT = 600;

            std::string title = "ex_lighting_texture";
            GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title.c_str(), NULL, NULL);
            m_window = window;
            if (window == nullptr)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return -1;
            }
            glfwMakeContextCurrent(window);

            // Connecting the callback function 'key_callback' to handle keyboard events
            //glfwSetKeyCallback(window, key_callback);

            //Call initialize function passed onn constructor

            // Loading all OpenGL function pointers with glad
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return -1;
            }

            // This must be executed after loading OpenGL with GLAD
            /* ImGui Start ---- */

            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 330");

            // Setting up the clear screen color
            glClearColor(0.85f, 0.85f, 0.85f, 1.0f);

            // As we work in 3D, we need to check which part is in front,
            // and which one is at the back enabling the depth testing
            glEnable(GL_DEPTH_TEST);


        }

        /// <summary>
        /// This function shuts down the window initialized
        /// </summary>
        void finishWindow() {
            /* ImGui Start ---- */
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            /* ImGui End ---- */

            // freeing GPU memory
            //gpuAxis.clear();
            //gpuWhiteDice.clear();
            //gpuBlueDice.clear();

            glfwTerminate();

        }

        /// <summary>
        /// Returns if window should be closed or not
        /// </summary>
        /// <returns>1 when should close, 0 instead.</returns>
        int shouldClose() {
           return !glfwWindowShouldClose(m_window);
        }

        /// <summary>
        /// This method does some configurations that should be inside the main loop
        /// </summary>
        void config_init() {
            {

                // Measuring performance
                //performanceMonitor.update(glfwGetTime());
                std::stringstream ss;
                glfwSetWindowTitle(m_window, ss.str().c_str());

                // Using GLFW to check and process input events
                glfwPollEvents();


                /* ImGui Start ---- */

                // feed inputs to dear imgui, start new frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                //Clearing the screen in both, color and depth
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                /* ImGui End ---- */

                {
                    /* ImGui Start ---- */

                    // render your GUI
                    ImGui::Begin("Statistics");


                    ImGui::End();

                    // Render dear imgui into screen
                    ImGui::Render();
                    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                    /* ImGui End ---- */
                }

                // Once the drawing is rendered, buffers are swap so an uncomplete drawing is never seen.
                glfwSwapBuffers(m_window);

            }
        }


	};



}