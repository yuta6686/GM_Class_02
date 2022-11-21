#pragma once
#include "gameObject.h"
#include "manager.h"
//  ---------------------------------------------------------
//  Factory [factory.h]
//                                  Author: Yanagisawa Yuta
//                                  Date  : 2022/11/19
//  ------------------------summary--------------------------
//  - このFactoryオブジェクトを継承して〇〇Factoryを作成する
// 
//  - Createで作ってシーンでAddGameObjectすれば、InitでCreateして
// 　　その後自動で消えてくれます。
// 
//  - 他のオブジェクトを生成する場合、privateに関数を作る
//  ---------------------------------------------------------

class Factory :public GameObject
{
protected:
    std::shared_ptr<Scene> _scene;
public:
    Factory() { _scene = Manager::GetScene(); }

    virtual void Init() override {
        // 作成したいインスタンスを作って
        Create();

        // 自分は消える
        SetDestroy();
    };

    virtual void Uninit() override {}
    virtual void Update() override {}
    virtual void Draw() override {}

    virtual void Create() = 0;
};