//AssetLoader.cpp

#include "Resource/AssetLoader.h"

void AssetLoader::AssetLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager){
    if(resource.type == "Texture"){
        TextureLoad();
    }
}