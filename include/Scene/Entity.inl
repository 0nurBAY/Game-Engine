//Entity.inl

#pragma once
template <typename C, typename... Args> C* Entity::AddComponent(Args&&... args){

    auto key = ComponentTypeID<C>();
    std::unique_ptr<C> comp = std::make_unique<C>(std::forward<Args>(args)...);
    comp->AddOwner(this);

    C* ptr = comp.get();

    if(inited){
        comp->AddOwner(this);
        comp->OnCreate();
        componenttypes |= static_cast<uint32_t>(comp->GetCategory());
    }
    components[key] = (std::move(comp));

    return ptr;
}
template <typename C> C* Entity::GetComponent() const{

    auto key = ComponentTypeID<C>();
    return static_cast<C*>(components[key].get());
}
template <typename C> bool Entity::HasComponent() const{
    
    auto key = ComponentTypeID<C>();
    return components[key] != nullptr;
}
// template <typename C> void Entity::RemoveComponent(){
//     auto key = ComponentTypeID<C>();
//     components.erase(key);
    
// }
