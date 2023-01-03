#pragma once
enum HANDLER 
{
	HANDLER_MONKEY,
	HANDLER_SQUIRREL,
	HANDLER_DOG,
};


// ハンドラのチェーンを構成するためのメソッドを宣言している
// リクエストを実行するためのメソッドも宣言している
class Handler
{
public :
	virtual int SetDepth(const int& depth) = 0;
	virtual Handler* SetNext(Handler* handler) = 0;
	virtual void RemoveNext() = 0;
	virtual std::string Handle(std::string request) = 0;
	virtual std::string ShowImGuiInformation() = 0;
};

// デフォルトの操作はベースハンドラクラスに実装する
class AbstractHandler : public Handler
{
private:
	Handler* _nextHandler;
	int _depth = 0;
public:	

	// Handler を介して継承されました	
	int SetDepth(const int& depth)override;

	virtual Handler* SetNext(Handler* handler) override;

	virtual std::string Handle(std::string request) override;
	
	virtual void RemoveNext() override;

	virtual std::string ShowImGuiInformation()override;
};

class MokeyHandler : public AbstractHandler
{
public:
	std::string Handle(std::string request) override;
};

class SquirrelHandler : public AbstractHandler
{
public:
	std::string Handle(std::string request) override;
};

class DogHandler : public AbstractHandler
{
public:
	std::string Handle(std::string request) override;
};

class ChainOfResponsibility : public ComponentObject
{
	Handler* _handler;
	std::map<HANDLER, Handler*> _handlers;

	std::string _request;
public:
	ChainOfResponsibility();
	void SetHandler(HANDLER handler,std::string request);
	void RemoveHandler();

	void InitInternal()override;
	void UninitInternal()override;
	void UpdateInternal()override;
	void DrawInternal()override;
	void DrawImguiInternal()override;
};