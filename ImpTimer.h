#ifndef IMP_TIMER_H
#define IMP_TIMER_H


class ImpTimer
{
    public:
        ImpTimer();
        virtual ~ImpTimer();

        void start();
        void stop();
        void paused();
        void unpaused();
        int get_ticks();
        bool is_started();
        bool is_paused();
    private:
        int start_tick;
        int paused_tick;

        bool is_paused_;
        bool is_started_;

};

#endif // IMPTIMER_H
