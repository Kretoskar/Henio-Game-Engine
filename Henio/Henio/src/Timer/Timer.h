#pragma once

namespace Henio
{

    class T_Timer
    {

    public:
        ~T_Timer();
        T_Timer(const T_Timer&) = delete;
        T_Timer& operator=(const T_Timer&) = delete;

        static T_Timer& Ref()
        {
            static T_Timer reference;
            return reference;
        }

        void Tick();
        void Initialize();
        float DeltaTime() { return deltaTime; }

    private:
        T_Timer();
        
        float lastFrame, deltaTime;
    };

    static T_Timer& Timer = T_Timer::Ref();
}
