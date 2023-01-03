#pragma once
enum HANDLER 
{
	HANDLER_MONKEY,
	HANDLER_SQUIRREL,
	HANDLER_DOG,
};


// �n���h���̃`�F�[�����\�����邽�߂̃��\�b�h��錾���Ă���
// ���N�G�X�g�����s���邽�߂̃��\�b�h���錾���Ă���
class Handler
{
public :
	virtual int SetDepth(const int& depth) = 0;
	virtual Handler* SetNext(Handler* handler) = 0;
	virtual void RemoveNext() = 0;
	virtual std::string Handle(std::string request) = 0;
	virtual std::string ShowImGuiInformation() = 0;
};

// �f�t�H���g�̑���̓x�[�X�n���h���N���X�Ɏ�������
class AbstractHandler : public Handler
{
private:
	Handler* _nextHandler;
	int _depth = 0;
public:	

	// Handler ����Čp������܂���	
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