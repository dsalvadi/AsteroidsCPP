#pragma once
#include <stack>
#include <memory>
#include <State.hpp>
using namespace std;

namespace Engine
{
    class StateMan
    {
        private:
        stack<unique_ptr<State>> m_stateStack;
        unique_ptr<State> m_newState;

        bool m_add, m_replace, m_remove;

        public:
        StateMan();
        ~StateMan();

        void Add(unique_ptr<State> toAdd, bool replace = false);
        void PopCurrent();
        void ProcessStateChange();
        unique_ptr<State>& GetCurrent();
    };
}