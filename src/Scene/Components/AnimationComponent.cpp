#include "Scene/Components/AnimationComponent.h"
#include "Scene/Entity.h"
#include "Event/Events.h"

AnimationComponent::AnimationComponent(){}

void AnimationComponent::AddAnimation(
    std::string state,
    Directions dir,
    const AssetHandle<Animation> &animation)
{
    // std::cout
    //     << "\n========================================\n"
    //     << "[AnimationComponent] ADD ANIMATION\n"
    //     << "  State      : " << state << "\n"
    //     << "  Direction  : " << static_cast<int>(dir) << "\n"
    //     << "  Animation  : " << animation.GetName() << "\n"
    //     << "========================================\n";

    animations[state][dir] = animation;
}

void AnimationComponent::AddQueue(std::string state, uint64_t queue)
{
    // std::cout
    //     << "\n----------------------------------------\n"
    //     << "[AnimationComponent] ADD QUEUE\n"
    //     << "  State      : " << state << "\n"
    //     << "  Priority   : " << queue << "\n"
    //     << "----------------------------------------\n";

    this->queue[state] = queue;
}

void AnimationComponent::OnEvent(Event &event)
{
    // std::cout
    //     << "\n========================================\n"
    //     << "[AnimationComponent] ON EVENT\n"
    //     << "  Event Type : " << static_cast<int>(event.GetType()) << "\n"
    //     << "  Category   : " << event.GetCategoryFlags() << "\n"
    //     << "========================================\n";

    EventDispatcher dispatcher(event);

    dispatcher.Dispatcher<StateChangeEvent>(
        [this](StateChangeEvent& event)
        {
            // std::cout
            //     << "[AnimationComponent] STATE CHANGE EVENT RECEIVED\n"
            //     << "  New State  : " << event.GetState() << "\n";

            RequestAnimation(event.GetState());
        });
}

void AnimationComponent::AnimationUpdate(
    float dt,
    ResourceManagerPlus* resourceManager)
{
    // std::cout
    //     << "\n\n"
    //     << "########################################\n"
    //     << "[AnimationComponent] ANIMATION UPDATE\n"
    //     << "  Delta Time  : " << dt << "\n"
    //     << "  Current     : " << current_state << "\n"
    //     << "  Request     : " << request << "\n"
    //     << "  Direction   : " << static_cast<int>(direction) << "\n"
    //     << "  Dir Request : " << static_cast<int>(directionrequest) << "\n"
    //     << "  Requests    : " << requests.size() << "\n"
    //     << "########################################\n";

    // 1. Önce gelen animation request'leri değerlendiriliyor.
    Play(resourceManager);

    // 2. Play() sonrasında hangi state/direction aktif onu görebilmek için.
    // std::cout
    //     << "\n[AnimationComponent] AFTER PLAY\n"
    //     << "  Current State : " << current_state << "\n"
    //     << "  Direction     : " << static_cast<int>(direction) << "\n"
    //     << "  Request       : " << request << "\n"
    //     << "  Dir Request   : " << static_cast<int>(directionrequest) << "\n";

    // 3. Aktif state + direction için animation aranıyor.
    auto animation = FindAnimation(resourceManager);

    if(!animation)
    {
        // std::cout
        //     << "[AnimationComponent] NO ANIMATION FOUND\n"
        //     << "  State     : " << current_state << "\n"
        //     << "  Direction : " << static_cast<int>(direction) << "\n";

        return;
    }

    // std::cout
    //     << "[AnimationComponent] ANIMATION READY\n"
    //     << "  Animation : " << animation->GetCurrentFrame() << "\n";

    // 4. Yeni animation seçildiyse bir kere resetleniyor.
    if(reset)
    {
        // std::cout
        //     << "[AnimationComponent] RESET ANIMATION\n";

        animation->Reset();
        reset = 0;
    }
    else
    {
        // 5. Mevcut animation frame'i ilerletiliyor.
        animation->Update(dt);

        // std::cout
        //     << "[AnimationComponent] UPDATE ANIMATION\n"
        //     << "  Delta Time : " << dt << "\n";
    }

    // 6. SpriteComponent bulunuyor.
    SpriteComponent* spritecomp =
        owner->GetComponent<SpriteComponent>();

    if(!spritecomp)
    {
        // std::cout
        //     << "[AnimationComponent] ERROR\n"
        //     << "  Entity '" << owner->GetName()
        //     << "' has no SpriteComponent\n";

        return;
    }

    // 7. Animation'ın o anki frame'i sprite'a aktarılıyor.
    spritecomp->SetSprite(animation->GetCurrentFrame());

    // std::cout
    //     << "[AnimationComponent] SPRITE UPDATED\n"
    //     << "  Entity : " << owner->GetName() << "\n"
    //     << "########################################\n";
}

void AnimationComponent::RequestAnimation(const std::string &name)
{
    // std::cout
    //     << "\n----------------------------------------\n"
    //     << "[AnimationComponent] REQUEST ANIMATION\n"
    //     << "  Requested : " << name << "\n"
    //     << "  Queue Size Before : " << requests.size() << "\n";

    requests.push_back(name);

    // std::cout
    //     << "  Queue Size After  : " << requests.size() << "\n"
    //     << "----------------------------------------\n";
}

void AnimationComponent::Play(
    ResourceManagerPlus* resourceManager)
{
    // std::cout
    //     << "\n[AnimationComponent] PLAY\n"
    //     << "  Before Decide:\n"
    //     << "    Current State : " << current_state << "\n"
    //     << "    Request       : " << request << "\n"
    //     << "    Current Dir   : " << static_cast<int>(direction) << "\n"
    //     << "    Request Dir   : " << static_cast<int>(directionrequest) << "\n"
    //     << "    Requests      : " << requests.size() << "\n";

    // Önce bekleyen request'lerden hangisinin seçileceğine karar ver.
    Decide();

    // std::cout
    //     << "  After Decide:\n"
    //     << "    Selected State : " << request << "\n";

    // State ve direction zaten aynıysa animation değiştirmeye gerek yok.
    if(current_state == request &&
       (direction == directionrequest||dirnon==true))
    {
        // std::cout
        //     << "[AnimationComponent] NO CHANGE\n"
        //     << "  State and direction are already active.\n";

        return;
    }

    auto old = current_state;
    auto old_dir = direction;

    // std::cout
    //     << "[AnimationComponent] CHANGING ANIMATION\n"
    //     << "  Old State : " << old << "\n"
    //     << "  New State : " << request << "\n"
    //     << "  Old Dir   : " << static_cast<int>(old_dir) << "\n"
    //     << "  New Dir   : " << static_cast<int>(directionrequest) << "\n";

    current_state = request;
    direction = directionrequest;

    // Yeni state + direction kombinasyonu gerçekten mevcut mu?
    auto animation = FindAnimation(resourceManager);

    if(!animation)
    {
        // std::cout
        //     << "[AnimationComponent] CHANGE FAILED\n"
        //     << "  Animation does not exist.\n"
        //     << "  Reverting to previous animation.\n";

        current_state = old;
        request = old;
        direction = old_dir;
        directionrequest = old_dir;

        return;
    }

    // std::cout
    //     << "[AnimationComponent] CHANGE SUCCESSFUL\n"
    //     << "  State     : " << current_state << "\n"
    //     << "  Direction : " << static_cast<int>(direction) << "\n";

    animation->Reset();
    reset = 0;
}

void AnimationComponent::Decide()
{
    // std::cout
    //     << "\n[AnimationComponent] DECIDE\n"
    //     << "  Number of requests : " << requests.size() << "\n";

    if(requests.empty())
    {
        // std::cout
        //     << "  No requests waiting.\n";

        return;
    }

    // std::cout
    //     << "  Pending requests:\n";

    for(auto& req : requests)
    {
        auto it = queue.find(req);

        if(it == queue.end())
        {
            // std::cout
            //     << "    - " << req
            //     << " | PRIORITY NOT FOUND\n";
        }
        else
        {
            // std::cout
            //     << "    - " << req
            //     << " | Priority : " << it->second << "\n";
        }
    }

    if(requests.size() == 1)
    {
        request = requests[0];

        // std::cout
        //     << "  Only one request.\n"
        //     << "  Selected : " << request << "\n";

        requests.clear();
        return;
    }

    std::string r;
    int i = -1;

    // std::cout
    //     << "  Comparing priorities...\n";

    for(auto& req : requests)
    {
        auto it = queue.find(req);

        if(it == queue.end())
        {
            // std::cout
            //     << "    Skipping " << req
            //     << " because it has no priority.\n";

            continue;
        }

        // std::cout
        //     << "    Checking : " << req
        //     << " | Priority : " << it->second
        //     << " | Current Highest : " << i
        //     << "\n";

        if(it->second < i)
            continue;

        r = req;
        i = it->second;
    }

    request = r;
    // owner->GetComponent<StateComponent>()->state = r;
    // std::cout
    //     << "  FINAL DECISION\n"
    //     << "    Selected State : " << request << "\n"
    //     << "    Priority       : " << i << "\n";

    requests.clear();

    // std::cout
    //     << "  Requests cleared.\n";
}

void AnimationComponent::Reset()
{
    // std::cout
    //     << "[AnimationComponent] RESET FLAG SET\n";

    reset = 1;
}

std::shared_ptr<Animation> AnimationComponent::FindAnimation(
    ResourceManagerPlus* resourceManager)
{
    // std::cout
    //     << "\n[AnimationComponent] FIND ANIMATION\n"
    //     << "  State     : " << current_state << "\n"
    //     << "  Direction : " << static_cast<int>(direction) << "\n";

    auto Outerit = animations.find(current_state);

    if(Outerit == animations.end())
    {
        // std::cout
        //     << "  State NOT FOUND in animation map.\n";

        return nullptr;
    }

    // std::cout
    //     << "  State found.\n"
    //     << "  Number of directions : "
    //     << Outerit->second.size() << "\n";

    if(Outerit->second.size() == 1)
    {
        dirnon=true;
        // std::cout
        //     << "  Only one animation exists.\n"
        //     << "  Using Direction::NONE.\n";

        direction = Directions::NONE;
    }else{dirnon=false;}

    auto it = Outerit->second.find(direction);

    if(it == Outerit->second.end())
    {
        // std::cout
        //     << "  Direction NOT FOUND.\n";

        return nullptr;
    }

    // std::cout
    //     << "  Animation FOUND\n"
    //     << "  Asset : " << it->second.GetName() << "\n";

    return resourceManager->Resolve<Animation>(
        it->second.GetName());
}

void AnimationComponent::SetDirection(Directions drequest)
{
    // std::cout
    //     << "\n[AnimationComponent] SET DIRECTION\n"
    //     << "  Old : " << static_cast<int>(directionrequest) << "\n"
    //     << "  New : " << static_cast<int>(drequest) << "\n";

    directionrequest = drequest;
}