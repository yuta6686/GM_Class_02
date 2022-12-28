#pragma once

enum ENEMY
{
    ENEMY_NORMAL,
    ENEMY_TRACKING,
    ENEMY_TRACKING_FAST,
    ENEMY_TRACKING_LATE,
    ENEMY_NO_DRUM,
    ENEMY_MOVE_STRAIGHT,
    ENEMY_JUMP,
    ENEMY_BOSS,
    ENEMY_MAX
};




class Enemy_Interface :
    public ComponentObject
{
private:
    class Audio* m_SEEnemyCollision;
    class Audio* m_SEEnemyKill;
protected:    
    int _maxHp=1;
    int _hp = _maxHp;
    static const int MAX_HP = 9999;
    int m_EnemyIndex = ENEMY_NORMAL;
    CountComponent* m_Count;
    D3DXVECTOR3 m_FirstScale;
    bool m_IsDestroy = false;
public:
    Enemy_Interface(const int& index)
        :m_EnemyIndex(index) {}
    
    virtual void Init();
    virtual void Update();
    virtual void Draw();

public: // セッター
    virtual bool SetHp(const int& hp);
    virtual bool SetMaxHp(const int& hp);
    void SetFirstScale(const D3DXVECTOR3& scale);
    void SetIndex(const int& index);
    void SetDiffuse(const D3DXCOLOR& color);

public: // ゲッター
    int GetMaxHp()const { return _maxHp; }
    int GetHp()const { return _hp; }    
    int GetEnemyIndex()const { return m_EnemyIndex; }

public: // その他
    void CollosionWithBullet();


};

