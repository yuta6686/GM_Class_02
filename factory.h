#pragma once
#include "gameObject.h"
#include "manager.h"
//  ---------------------------------------------------------
//  Factory [factory.h]
//                                  Author: Yanagisawa Yuta
//                                  Date  : 2022/11/19
//  ------------------------summary--------------------------
//  - ����Factory�I�u�W�F�N�g���p�����āZ�ZFactory���쐬����
// 
//  - Create�ō���ăV�[����AddGameObject����΁AInit��Create����
// �@�@���̌㎩���ŏ����Ă���܂��B
// 
//  - ���̃I�u�W�F�N�g�𐶐�����ꍇ�Aprivate�Ɋ֐������
//  ---------------------------------------------------------

class Factory :public GameObject
{
protected:
    std::shared_ptr<Scene> _scene;
public:
    Factory() { _scene = Manager::GetScene(); }

    virtual void Init() override {
        // �쐬�������C���X�^���X�������
        Create();

        // �����͏�����
        SetDestroy();
    };

    virtual void Uninit() override {}
    virtual void Update() override {}
    virtual void Draw() override {}

    virtual void Create() = 0;
};