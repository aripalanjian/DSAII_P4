#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

class Heuristic{

    public:
        void onlineFirst();
        void onlineNext();
        void onlineBest();

        void offlineFirst();
        void offlineBest();

        void getSnapshot();
};

#endif