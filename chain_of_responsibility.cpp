#include "stdafx.h"
#include "chain_of_responsibility.h"

ChainOfResponsibility::ChainOfResponsibility()
{
    _handlers[HANDLER::HANDLER_MONKEY] = new MokeyHandler();
    _handlers[HANDLER::HANDLER_SQUIRREL] = new SquirrelHandler();
    _handlers[HANDLER::HANDLER_DOG] = new DogHandler();

    _handler = nullptr;    
}

void ChainOfResponsibility::SetHandler(HANDLER handler, std::string request)
{
    _request = request;

    // “¯‚¶‚à‚Ì‚È‚Ì‚Å•Ô‚·
    if (_handler == _handlers[handler])return;

    // Å‰
    if(_handler == nullptr)
    {
        _handler = _handlers[handler];
    }
    // 2‚Â–ÚˆÈ~
    else 
    {
        _handler->SetNext(_handlers[handler]);
    }
}

void ChainOfResponsibility::RemoveHandler()
{
    if (_handler) 
    {
        _handler->RemoveNext();        
        _handler = nullptr;
    }

}

void ChainOfResponsibility::InitInternal()
{
    AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIsUse(true);
}

void ChainOfResponsibility::UninitInternal()
{
    for (auto handler : _handlers)
    {        
        delete handler.second;
        handler.second = nullptr;
    }
    _handlers.clear();
}

void ChainOfResponsibility::UpdateInternal()
{
    if (GetKeyboardTrigger(DIK_R)) 
    {
        RemoveHandler();
    }

    if (GetKeyboardTrigger(DIK_1))
    {
        SetHandler(HANDLER_MONKEY, "Banana");
    }
    if (GetKeyboardTrigger(DIK_2))
    {
        SetHandler(HANDLER_SQUIRREL, "Nut");
    }
    if (GetKeyboardTrigger(DIK_3))
    {
        SetHandler(HANDLER_DOG, "MeatBall");
    }
}

void ChainOfResponsibility::DrawInternal()
{
}

void ChainOfResponsibility::DrawImguiInternal()
{
    if (_handler == nullptr)return;
    
    
    ImGui::Text(_handler->Handle(_request).c_str());

    ImGui::Separator();

    ImGui::Text(_handler->ShowImGuiInformation().c_str());
}

int AbstractHandler::SetDepth(const int& depth)
{
    _depth = depth;
    return depth;
}

Handler* AbstractHandler::SetNext(Handler* handler)
{
    if (handler == this)return nullptr;

    if(this->_nextHandler == nullptr)
    {
        this->_nextHandler = handler;        
    }
    else 
    {
        this->_nextHandler->SetNext(handler);
    }

    this->_nextHandler->SetDepth(this->_depth + 1);

    return handler;
}

std::string AbstractHandler::Handle(std::string request)
{
    if (this->_nextHandler)     
    {
        return this->_nextHandler->Handle(request);
    }
    
    return "";
}

void AbstractHandler::RemoveNext()
{
    if (_nextHandler) {
        _nextHandler->RemoveNext();
        
        _nextHandler = nullptr;
    }
}

std::string AbstractHandler::ShowImGuiInformation()
{
    const std::type_info& info = typeid(this);
    std::string info_str = std::to_string(_depth) + info.name() + "\n";

    if (_nextHandler) 
    {
        return info_str + _nextHandler->ShowImGuiInformation();
    }
    
    return info_str;
}

std::string MokeyHandler::Handle(std::string request)
{
    if (request == "Banana")
    {
        return "Monkey: I'll eat the " + request + ".\n";
    }
    else if (request == "Nut")
    {
        return AbstractHandler::Handle("Monkey_" + request);
    }
    else 
    {
        return AbstractHandler::Handle(request);
    }    
}

std::string SquirrelHandler::Handle(std::string request)
{
    if (request == "Nut")
    {
        return "Squirrel: I'll eat the " + request + ".\n";
    }
    else if (request == "Monkey_Nut") 
    {
        return "Squirrel: I'll eat the " + request + ".\n";
    }
    else
    {
        return AbstractHandler::Handle(request);
    }
}

std::string DogHandler::Handle(std::string request)
{
    if (request == "MeatBall")
    {
        return "Dog: I'll eat the " + request + ".\n";
    }
    else
    {
        return AbstractHandler::Handle(request);
    }
}
