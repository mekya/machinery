//
//  Class: Kerberos
//	Description: Entry point of application.
//  Created:     17/07/2014
//  Author:      Cédric Verstraeten
//  Mail:        hello@cedric.ws
//	Website:	 www.kerberos.io
//
//  The copyright to the computer program(s) herein
//  is the property of kerberos.io, Belgium.
//  The program(s) may be used and/or copied .
//
/////////////////////////////////////////////////////

#ifndef __Kerberos_H_INCLUDED__   // if Kerberos.h hasn't been included yet...
#define __Kerberos_H_INCLUDED__   // #define this so the compiler knows it has been included

#include "Factory.h"
#include "machinery/Machinery.h"
#include "Guard.h"
#include "document.h" // rapidjson
#include "capture/Stream.h"

namespace kerberos
{
    class Kerberos
    {
        private:

            Kerberos(){};
            ~Kerberos(){delete guard; delete capture; delete machinery;};

            void bootstrap(StringMap & parameters);
            void configure(const std::string & configuration);
            void configureCapture(StringMap & settings);
            void configureCloud(StringMap & settings);
            void startStreamThread();
            void stopStreamThread();
            void startIOThread();
            void stopIOThread();

            void setCaptureDelayTime(int delay){m_captureDelayTime=delay;};
            void setParameters(StringMap & parameters){m_parameters = parameters;};
            StringMap getParameters(){return m_parameters;}
        
        public:

            Cloud * cloud;
            Machinery * machinery;
            Capture * capture;
            Stream * stream;
            pthread_t m_streamThread;
            pthread_mutex_t m_streamLock;
            pthread_t m_ioThread;
            pthread_mutex_t m_ioLock;
            pthread_mutex_t m_cloudLock;
            DetectionVector m_detections;
            FW::Guard * guard;

            ImageVector m_images;
            int m_captureDelayTime;
            StringMap m_parameters;

            // -----------
            // Singleton

            static Kerberos * getInstance()
            {
                static Kerberos _kerberos;
                return &_kerberos;
            }

            // ----------------
            // Run application

            static void run(StringMap & parameters)
            {
                getInstance()->bootstrap(parameters);
            }

            // -----------------------------------
            // Alias for configure, more readable
            
            static void reconfigure(const std::string & configuration)
            {
                getInstance()->configure(configuration);
            }
    };
}
#endif
