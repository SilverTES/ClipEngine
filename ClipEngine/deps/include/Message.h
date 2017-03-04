#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

#include <deque>
#include <cstdio>

#include "Clip.h"

static unsigned uniqueMessageId = 0;

struct MessageData
{

};


struct Message
{
    unsigned _id = 0;
    int _type = -1;
    MessageData* _data = nullptr;
    Clip* _to = nullptr;
    Clip* _from = nullptr;

    Message(int type, MessageData* data, Clip* to, Clip* from = nullptr)
    {
        _id = uniqueMessageId;
        _type = type;
        _data = data;
        _to = to;
        _from = from;
        ++uniqueMessageId;
    }

    static void kill(Clip* clip)
    {
        if (nullptr != clip->_message)
        {
            delete clip->_message->_data;
            clip->_message->_data = nullptr;
            delete clip->_message;
            clip->_message = nullptr;
        }
    }

};


class MessageQueue
{
    public:
        MessageQueue()
        {
            clearAll();
        }
        ~MessageQueue()
        {

        }

        void add(Message* message)
        {
            if (nullptr != message)
                _deqMessage.push_front(message);
        }

        int post(int type, MessageData* data, Clip* to, Clip* from = nullptr)
        {
            // if to is null then don't post anything
            Message* message = new Message(type, data, to, from);
            if (nullptr != to)
                add(message);

            return message->_id;
        }

        bool isEmpty()
        {
            return _deqMessage.empty();
        }

        void clearAll()
        {
            if (!_deqMessage.empty())
            {
                for (auto & it: _deqMessage)
                {
                    if (nullptr != it)
                    {
                        if (nullptr != it->_data)
                            delete it->_data;

                        it->_data = nullptr;

                        delete it;
                        it = nullptr;
                    }
                }
                _deqMessage.clear();
            }
        }

        Message* message()
        {
            if (_deqMessage.empty())
                return nullptr;
            else
                return _deqMessage.back();
        }

        unsigned lastMessageId()
        {
            return message()->_id;
        }

        MessageData* lastMessageData()
        {
            return message()->_data;
        }

        Clip* from()
        {
            if (nullptr != message())
                return message()->_from;
            else
                return nullptr; // nobody
        }

        Clip* to()
        {
            if (nullptr != message())
                return message()->_to;
            else
                return nullptr; // nobody
        }

        void* data()
        {
            if (nullptr != message())
                return message()->_data;
            else
                return nullptr; // nothing
        }

        int getMessageType()
        {
            if (nullptr != message())
                return message()->_type;
            else
                return -1;
        }

        void dispatch()
        {
            for
            (
                auto it = _deqMessage.rbegin();
                it != _deqMessage.rend();
                ++it
            )
            {
                if (nullptr != (*it))
                {
                    // if Clip exist
                    if (nullptr != (*it)->_to)
                    {
                        (*it)->_to->_message = (*it);
                    }

                    _deqMessage.pop_back();
                }
            }
        }


        void showAll()
        {
            unsigned index = 0;
            for (auto & it: _deqMessage)
            {
                printf
                (
                    "- Message %i : %s , %s , %i \n",
                    index,
                    it->_from->_name.c_str(),
                    it->_to->_name.c_str(),
                    it->_type
                );
                ++index;
            }
        }

    protected:

    private:

    std::deque<Message*> _deqMessage;

};



#endif // MESSAGE_H_INCLUDED
