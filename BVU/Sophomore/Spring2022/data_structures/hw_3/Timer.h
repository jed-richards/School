#include <chrono>

class Timer {
    
    private: 
        float time;
        long long int startTime, stopTime, elapsedTime, longTime, checkTime;
        bool running;
    
    public:
        Timer() {
            time = 0;                
            running = false;
            startTime = 0;
            stopTime = 0;
            elapsedTime = 0;
        }   

        void start() {
            if (running == false) {
                running = true;
                startTime = now();
            }
            //else its already running
        }

        void stop() {
            if (running == true) { 
                running = false;
                stopTime = now();
                elapsedTime += deltaTime(startTime, stopTime); 
            }
            //else its not running so can't stop
        }
        void clear() {
            elapsedTime = 0;
            startTime = now();
        }

        float getTime() {
            if (running == true) {
                checkTime = now();
                time = convertTime(elapsedTime + deltaTime(startTime, checkTime));
            }
            else {
                time = convertTime(elapsedTime);
            }
            return time;
        }
            
    private:
        // A private member function that you may find useful as you implement
        // the functions listed above. It fetches the number of microseconds that
        // have passed since 12:00 AM on Jan 1, 1970
        // Don't worry too much about how it works right now; just trust me! :)
        long long int now() {
            using namespace std::chrono;
            duration<double, std::micro> t = system_clock::now().time_since_epoch();
            return t.count();
        }


        // Here I write my own private functions called deltaTime and converTime
        
        // deltaTime() takes in two times and returns final - intial 
        long long int deltaTime(long long int initialTime, long long int finalTime) {
            return (finalTime - initialTime);
        }
        
        // converTime() takes in one long long int in microseconds and converts it into a float in seconds
        float convertTime(long long int longTime) {
            return longTime/1000000.0;
        }

};




