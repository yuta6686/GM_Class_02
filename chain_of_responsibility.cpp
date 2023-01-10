#include "stdafx.h"
#include "chain_of_responsibility.h"
#include "co_prism.h"
#include "prism_factory.h"

ChainOfResponsibility::ChainOfResponsibility()
{
    _handlers[HANDLER::HANDLER_MOVE] = new MoveHandler();    
    _handlers[HANDLER::HANDLER_SCALE] = new ScaleHandler();
    _handlers[HANDLER::HANDLER_X] = new XHandler();
    _handlers[HANDLER::HANDLER_Y] = new YHandler();
    _handlers[HANDLER::HANDLER_Z] = new ZHandler();

    _handler = nullptr;    
}

void ChainOfResponsibility::SetHandler(HANDLER handler, std::string request)
{    
    _request = request;

    // Å‰
    if(_handler == nullptr)
    {
        _handler = _handlers[handler];
    }
    // 2‚Â–ÚˆÈ~
    else 
    {        
        // “¯‚¶‚à‚Ì‚È‚Ì‚Å•Ô‚·
        if (_handler->HasSameHandler(_handlers[handler]))
        {
            //RemoveHandler();
            return;
        }

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
    if (GetKeyboardTrigger(DIK_R) || IsMouseLeftTriggered()) 
    {
        RemoveHandler();
    }

    if (GetKeyboardTrigger(DIK_G))
    {
        SetHandler(HANDLER_MOVE, MoveHandler::REQUEST);
    }
    if (GetKeyboardTrigger(DIK_X))
    {
        SetHandler(HANDLER_X, XHandler::REQUEST);
    }
    if (GetKeyboardTrigger(DIK_Y))
    {
        SetHandler(HANDLER_Y, YHandler::REQUEST);
    }
    if (GetKeyboardTrigger(DIK_Z))
    {
        SetHandler(HANDLER_Z, ZHandler::REQUEST);
    }

    if (GetKeyboardTrigger(DIK_S))
    {
        SetHandler(HANDLER_SCALE, ScaleHandler::REQUEST);
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

void ChainOfResponsibility::UpdateHandler()
{
    if (!_handler)return;
    _handler->Update(_request);
}

void ChainOfResponsibility::SetCurrentPrism(CO_Prism* prism, PrismGenerateParameter* param)
{
    if (!_handler)return;
    _handler->SetCurrentPrism(prism,param);
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

bool AbstractHandler::HasSameHandler(Handler* handler)
{
    // ŒŸõ‚³‚ê‚Ä‚¢‚éHandler‚ªŽ©•ª‚©?
    if (handler == this)return true;

    // nextHandler‚ª‚¢‚ê‚ÎŒŸõ‚·‚é1
    if (_nextHandler) 
    {
        return _nextHandler->HasSameHandler(handler);
    }

    // ‚¢‚È‚©‚Á‚½‚ç
    return false;
}

void AbstractHandler::RemoveNext()
{
    if (_nextHandler) {
        _nextHandler->SetDepth(0);
        _nextHandler->RemoveNext();

        _nextHandler = nullptr;
    }
}

std::string AbstractHandler::ShowImGuiInformation()
{    
    std::string info_str = std::to_string(_depth) + _handlerName + "\n";    

    if (_nextHandler) 
    {
        return info_str + _nextHandler->ShowImGuiInformation();
    }
    
    return info_str;
}

void AbstractHandler::SetCurrentPrism(CO_Prism* prism, PrismGenerateParameter* param)
{    
    _prismParameter = param;
    _prism = prism;

    if (_nextHandler) 
    {
        _nextHandler->SetCurrentPrism(prism,param);
    }
}

void AbstractHandler::Update(std::string request)
{
    if (this->_nextHandler)
    {
        this->_nextHandler->Update(request);
    }    
}

std::string MoveHandler::Handle(std::string request)
{
    if (request == MoveHandler::REQUEST)
    {
        return request;
    }
    /*else if (request == this->REQUEST + XHandler::REQUEST) 
    {
        return AbstractHandler::Handle(this->REQUEST + request);
    }*/
    else 
    {
        return AbstractHandler::Handle(this->REQUEST + request);
    }    
}

void MoveHandler::Update(std::string request)
{
    if (request == this->REQUEST)
    {
        return;
    }
    else if (request == XHandler::REQUEST)
    {
        return AbstractHandler::Update(this->REQUEST + request);
    }
    else
    {
        return AbstractHandler::Update(this->REQUEST + request);
    }
}

std::string ScaleHandler::Handle(std::string request)
{
    if (request == this->REQUEST)
    {
        return request;
    }
    else
    {
        return AbstractHandler::Handle(this->REQUEST + request);
    }
}

void ScaleHandler::Update(std::string request)
{
    if (request == this->REQUEST)
    {
        return;
    }
    else
    {
        return AbstractHandler::Update(this->REQUEST + request);
    }
}

std::string XHandler::Handle(std::string request)
{
    if (request == this->REQUEST)
    {
        return request;
    }
    else if (request == MoveHandler::REQUEST + this->REQUEST)
    {
        
       

        return request;
    }
    else if (request == ScaleHandler::REQUEST + this->REQUEST)
    {
        if (!_prism)return request;

        D3DXMATRIX screen, world, view, proj;
        world = _prism->GetComponent<MatrixComponent>()->GetWorldMatrix();
        view = _prism->_camera->GetViewMatrix();
        proj = _prism->_camera->GetProjectionMatrix();

        D3DXMatrixIdentity(&screen);
        screen = world * view * proj;

        D3DXVECTOR4 viewPosition,projectionPosition,pos;
        pos = { _prismParameter->_position,1.0f };

        D3DXVec4Transform(&viewPosition, &pos, &view); 
        D3DXVec4Transform(&projectionPosition, &viewPosition, &proj);
        projectionPosition /= projectionPosition.w;

        D3DXVECTOR2 screenPosition;
        screenPosition.x = (1.0f + projectionPosition.x) / 2.0f * SCREEN_WIDTH;
        screenPosition.x = (1.0f - projectionPosition.y) / 2.0f * SCREEN_HEIGHT;
        ImGui::Text("x: %.2f\n", screenPosition.x);
        ImGui::Text("y: %.2f\n", screenPosition.y);

        //ImGui::Text("11: %.2f\n", view._11);
        //ImGui::Text("12: %.2f\n", view._12);
        //ImGui::Text("13: %.2f\n", view._13);
        //ImGui::Text("14: %.2f\n", view._14);
        //ImGui::Text("21: %.2f\n", view._21);
        //ImGui::Text("22: %.2f\n", view._22);
        //ImGui::Text("23: %.2f\n", view._23);
        //ImGui::Text("24: %.2f\n", view._24);
        //ImGui::Text("31: %.2f\n", view._31);
        //ImGui::Text("32: %.2f\n", view._32);
        //ImGui::Text("33: %.2f\n", view._33);
        //ImGui::Text("34: %.2f\n", view._34);
        //ImGui::Text("41: %.2f\n", view._41); // x
        //ImGui::Text("42: %.2f\n", view._42); // y
        //ImGui::Text("43: %.2f\n", view._43); // z
        //ImGui::Text("44: %.2f\n", view._44);


        return request;
    }
    else if (request == this->REQUEST + MoveHandler::REQUEST)
    {
        // ‚±‚Ì‚Æ‚«‚ÉRemove‚³‚¹‚½‚¢

        return request;
    }
    else
    {
        return AbstractHandler::Handle(request);
    }
}

void XHandler::Update(std::string request)
{
    if (request == this->REQUEST)
    {
        return ;
    }
    else if (request == MoveHandler::REQUEST + this->REQUEST)
    {
        float dx = ImGui::GetIO().MouseDelta.x * 0.1f;        

        if (_prismParameter)
            _prismParameter->_position.x += dx;

        return ;
    }
    else if (request == ScaleHandler::REQUEST + this->REQUEST)
    {


        return ;
    }
    else
    {
        return AbstractHandler::Update(request);
    }
}

std::string YHandler::Handle(std::string request)
{
    if (request == this->REQUEST)
    {
        return request;
    }
    else if (request == MoveHandler::REQUEST + this->REQUEST) 
    {
        return request;
    }
    else if (request == ScaleHandler::REQUEST + this->REQUEST)
    {



        return request;
    }
    else
    {
        return AbstractHandler::Handle(request);
    }
}

void YHandler::Update(std::string request)
{
    if (request == this->REQUEST)
    {
        return ;
    }
    else if (request == MoveHandler::REQUEST + this->REQUEST)
    {
        float dy = ImGui::GetIO().MouseDelta.y * 0.1f;

        if (_prismParameter)
            _prismParameter->_position.y -= dy;

        return;
    }
    else if (request == ScaleHandler::REQUEST + this->REQUEST)
    {



        return ;
    }
    else
    {
        return AbstractHandler::Update(request);
    }
}

std::string ZHandler::Handle(std::string request)
{
    if (request == this->REQUEST)
    {
        return request;
    }
    else if (request == MoveHandler::REQUEST + this->REQUEST)
    {
        return request;
    }
    else if (request == ScaleHandler::REQUEST + this->REQUEST)
    {



        return request;
    }
    else
    {
        return AbstractHandler::Handle(request);
    }
}

void ZHandler::Update(std::string request)
{
    if (request == this->REQUEST)
    {
        return;
    }
    else if (request == MoveHandler::REQUEST + this->REQUEST)
    {

        return ;
    }
    else if (request == ScaleHandler::REQUEST + this->REQUEST)
    {



        return ;
    }
    else
    {
        return AbstractHandler::Update(request);
    }
}
