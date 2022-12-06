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
    int m_MaxHp=1;
    int m_Hp = m_MaxHp;
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
    int GetMaxHp()const { return m_MaxHp; }
    int GetHp()const { return m_Hp; }    
    int GetEnemyIndex()const { return m_EnemyIndex; }

public: // その他
    void CollosionWithBullet();

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(CEREAL_NVP(m_Position.x), CEREAL_NVP(m_Position.y), CEREAL_NVP(m_Position.z));
    }
};

