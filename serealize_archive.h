#pragma once
template<class Archive>
void serialize(Archive& archive, D3DXVECTOR3& vector) {
    archive(cereal::make_nvp("x", vector.x),
        cereal::make_nvp("y", vector.y),
        cereal::make_nvp("z", vector.z));
}