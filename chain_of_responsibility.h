#pragma once
/** ---------------------------------------------------------
 *  [chain_of_responsibility.h]
 *                                 @author: yuta.yanagisawa
 *                                 @date  : 2023/1/3
 * ------------------------summary--------------------------
 * @brief コマンド機能の実装
 * 
 * @link https://yuta6686.atlassian.net/browse/AS-8
 ** ---------------------------------------------------------*/

class CO_Prism;
class PrismGenerateParameter;

enum HANDLER 
{
	HANDLER_MOVE,
	HANDLER_SCALE,
	HANDLER_X,
	HANDLER_Y,
	HANDLER_Z,
};


// ハンドラのチェーンを構成するためのメソッドを宣言している
// リクエストを実行するためのメソッドも宣言している
class Handler
{
public :
	virtual int SetDepth(const int& depth) = 0;
	virtual Handler* SetNext(Handler* handler) = 0;
	virtual bool HasSameHandler(Handler* handler) = 0;
	virtual void RemoveNext() = 0;
	virtual std::string Handle(std::string request) = 0;
	virtual void Update(std::string request) = 0;
	virtual std::string ShowImGuiInformation() = 0;
	
	virtual void SetCurrentPrism(CO_Prism* prism,PrismGenerateParameter* param) = 0;
};

// デフォルトの操作はベースハンドラクラスに実装する
class AbstractHandler : public Handler
{
private:
	Handler* _nextHandler;
	int _depth = 0;
	std::string _handlerName;
protected:
	PrismGenerateParameter* _prismParameter;
	CO_Prism* _prism;
public:	
	AbstractHandler() = default;
	AbstractHandler(std::string handlerName) :
		_handlerName(handlerName),
		_nextHandler(nullptr), 
		_depth(0)
	{}

	// Handler を介して継承されました	
	int SetDepth(const int& depth)override;

	virtual bool HasSameHandler(Handler* handler)override;

	virtual Handler* SetNext(Handler* handler) override;

	virtual std::string Handle(std::string request) override;

	virtual void Update(std::string request)override;
	
	virtual void RemoveNext() override;

	virtual std::string ShowImGuiInformation()override;	

	virtual void SetCurrentPrism(CO_Prism* prism, PrismGenerateParameter* param)override;
};

class MoveHandler : public AbstractHandler
{
public:
	static inline const std::string REQUEST = "MOVE";
public:
	MoveHandler():AbstractHandler(REQUEST) {};
	std::string Handle(std::string request) override;
	void Update(std::string request) override;
};

class ScaleHandler : public AbstractHandler
{
public:
	static inline const std::string REQUEST = "SCALE";
public:
	ScaleHandler() :AbstractHandler(REQUEST) {};
	std::string Handle(std::string request) override;
	void Update(std::string request) override;
};

class XHandler : public AbstractHandler
{
public:
	static inline const std::string REQUEST = "X";
public:
	XHandler() :AbstractHandler(REQUEST) {};
	std::string Handle(std::string request) override;
	void Update(std::string request) override;
};

class YHandler : public AbstractHandler
{
public:
	static inline const std::string REQUEST = "Y";
public:
	YHandler() :AbstractHandler(REQUEST) {};
	std::string Handle(std::string request) override;
	void Update(std::string request) override;
};

class ZHandler : public AbstractHandler
{
public:
	static inline const std::string REQUEST = "Z";
public:	
	ZHandler() :AbstractHandler(REQUEST) {};
	std::string Handle(std::string request) override;
	void Update(std::string request) override;
};

class ChainOfResponsibility : public ComponentObject
{
	AbstractHandler* _handler;
	std::map<HANDLER, AbstractHandler*> _handlers;

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
	void SetCurrentPrism(CO_Prism* prism, PrismGenerateParameter* param);
	void UpdateHandler();
};