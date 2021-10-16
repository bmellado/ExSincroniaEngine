#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <cmath>
#include <ciso646>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <grafica/shape.h>
#include <grafica/basic_shapes.h>
#include <grafica/load_shaders.h>
#include <grafica/performance_monitor.h>
#include <grafica/easy_shaders.h>
#include <grafica/gpu_shape.h>
#include <grafica/transformations.h>


namespace Sincronia {

    void joystick_callback(int jid, int event)
    {
        if (event == GLFW_CONNECTED)
        {
            // The joystick was connected
            std::cout << "The joystick " << jid << " was connected" << std::endl;
        }
        else if (event == GLFW_DISCONNECTED)
        {
            // The joystick was disconnected
            std::cout << "The joystick " << jid << " was disconnected" << std::endl;
        }
    }

    /* A simple struct handling all axes and button inputs of a joystick. */
    struct Joystick
    {
        std::vector<bool> buttons;
        std::vector<float> axes;

        Joystick(std::size_t const numberOfButtons, std::size_t const numberOfAxes) :
            buttons(numberOfButtons, false), axes(numberOfAxes, 0.0f)
        {
        }
    };

    std::ostream& operator<<(std::ostream& os, const Joystick& joystick)
    {
        os << "buttons: ";
        for (bool button : joystick.buttons)
        {
            os << (button ? 1 : 0);
        }
        os << " axes: ";
        for (float ax : joystick.axes)
        {
            os << std::fixed << std::setprecision(2) << std::setfill('0') << ax << " ";
        }
        return os;
    }

    /* A convenient type to identify specific joysticks. */
    using JoystickId = std::size_t;

    /* Convenient storage for all joysticks. They can be accessed by their id.
     * Do note that due to connections and disconnections, the joystick ids may not be succesive numbers.
     * This way, to use an std::vector would require additional logic. */
    using JoystickContainer = std::unordered_map<JoystickId, Joystick>;

    /* joysticks is not const as we detect connections and disconnections of joystics. */
    void pollJoysticks(JoystickContainer& joysticks)
    {
        for (int joystickId = GLFW_JOYSTICK_1; joystickId < GLFW_JOYSTICK_LAST; ++joystickId)
        {
            int const joystickConnected = glfwJoystickPresent(joystickId);
            if (joystickConnected == GLFW_FALSE)
            {
                if (joysticks.count(joystickId) != 0)
                {
                    /* joystickId has been disconnected.*/
                    joysticks.erase(joystickId);
                }
                continue;
            }

            // At this point we have a joystick with this id.
            if (joysticks.count(joystickId) == 0)
            {
                /* joystickId has been connected.*/

                int buttonsCount;
                glfwGetJoystickButtons(joystickId, &buttonsCount);

                int axesCount;
                glfwGetJoystickAxes(joystickId, &axesCount);

                joysticks.emplace(joystickId, Joystick(buttonsCount, axesCount));
            }

            Joystick& joystick = joysticks.at(joystickId);

            int buttonsCount;
            const unsigned char* buttons = glfwGetJoystickButtons(joystickId, &buttonsCount);
            assert(joystick.buttons.size() == buttonsCount);

            for (int buttonId = 0; buttonId < buttonsCount; ++buttonId)
            {
                joystick.buttons[buttonId] = buttons[buttonId] == GLFW_PRESS;
            }

            int axesCount;
            const float* axes = glfwGetJoystickAxes(joystickId, &axesCount);
            assert(joystick.axes.size() == axesCount);

            for (int axesId = 0; axesId < axesCount; ++axesId)
            {
                joystick.axes[axesId] = axes[axesId];
            }
        }
    }

    void setJoystickCallBack() {
        glfwSetJoystickCallback(joystick_callback);
    }

}


