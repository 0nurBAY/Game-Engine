//Entity.inl

#pragma once
template <typename C, typename... Args> C* Entity::AddComponent(Args&&... args){

    auto key = std::type_index(typeid(C));

    auto it = components.find(key);
    if(it != components.end()) return static_cast<C*>(it->second.get());

    std::unique_ptr<C> comp = std::make_unique<C>(std::forward<Args>(args)...);
    comp->AddOwner(this);

    C* ptr = comp.get();

    components.insert({key,std::move(comp)});

    return ptr;
}
template <typename C> C* Entity::GetComponent(){

    auto key = std::type_index(typeid(C));
    auto it = components.find(key);
    if(it != components.end()) return static_cast<C*>(it->second.get());
    return nullptr;
}
template <typename C> bool Entity::HasComponent(){
    
    auto key = std::type_index(typeid(C));
    return components.find(key) != components.end();
}
template <typename C> void Entity::RemoveComponent(){
    
    // auto key = std::type_index(typeid(C));
    // auto it = components.find(key);
    // if(it != components.end()) components.erase(key);
    auto key = std::type_index(typeid(C));
    components.erase(key);
    
}
