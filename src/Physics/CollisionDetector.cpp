//CollisionDetector.cpp
#include "Physics/CollisionDetector.h"

ColliderResult CollisionDetector::CircleVsCircle(ColliderShape* shape1, ColliderShape* shape2, glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2){
    glm::vec2 collider1Pos = shape1->GetWorldTransform(pos1,rot1).position;
    glm::vec2 collider2Pos = shape2->GetWorldTransform(pos2,rot2).position;
    glm::vec2 normal = glm::normalize(collider2Pos - collider1Pos);
    float distance = glm::distance(collider1Pos, collider2Pos);
    float radius1 = dynamic_cast<CircleShape*>(shape1)->GetRadius();
    float radius2 = dynamic_cast<CircleShape*>(shape2)->GetRadius();
    float sumOfRadii = radius1 + radius2;
    ColliderResult res = {distance <= sumOfRadii,normal,sumOfRadii-distance,collider1Pos,collider2Pos,{(radius1 * normal) + collider1Pos,(radius2 * -normal) + collider2Pos}};
    // res.radius1 = radius1;
    // res.radius2 = radius2;
    return res;

}

ColliderResult CollisionDetector::BoxVsBox(ColliderShape* shape1, ColliderShape* shape2, glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2)
{   
    BoxShape* shapeA = dynamic_cast<BoxShape*>(shape1);
    BoxShape* shapeB = dynamic_cast<BoxShape*>(shape2);
    Transform2D A = shapeA->GetWorldTransform(pos1,rot1);
    Transform2D B = shapeB->GetWorldTransform(pos2,rot2);
    float cosA = glm::cos(glm::radians(A.rotation));
    float sinA = glm::sin(glm::radians(A.rotation));
    float cosB = glm::cos(glm::radians(B.rotation));
    float sinB = glm::sin(glm::radians(B.rotation));
    glm::vec2 Axixes[4] ={
        glm::vec2(cosA,sinA),
        glm::vec2(-sinA,cosA),
        glm::vec2(cosB,sinB),
        glm::vec2(-sinB,cosB)
    };
    glm::vec2 CoordinatesA[4] ={
        A.position+glm::vec2(shapeA->Gethalves().x*cosA-shapeA->Gethalves().y*sinA,shapeA->Gethalves().y*cosA+shapeA->Gethalves().x*sinA), //Top Right
        A.position+glm::vec2(-shapeA->Gethalves().x*cosA-shapeA->Gethalves().y*sinA,shapeA->Gethalves().y*cosA-shapeA->Gethalves().x*sinA),//Top Left
        A.position+glm::vec2(shapeA->Gethalves().x*cosA+shapeA->Gethalves().y*sinA,-shapeA->Gethalves().y*cosA+shapeA->Gethalves().x*sinA),//Bottom Right
        A.position+glm::vec2(-shapeA->Gethalves().x*cosA+shapeA->Gethalves().y*sinA,-shapeA->Gethalves().y*cosA-shapeA->Gethalves().x*sinA)//Bottom Left
    };
    
    glm::vec2 CoordinatesB[4] ={
        B.position+glm::vec2(shapeB->Gethalves().x*cosB-shapeB->Gethalves().y*sinB,shapeB->Gethalves().y*cosB+shapeB->Gethalves().x*sinB), //Top Right
        B.position+glm::vec2(-shapeB->Gethalves().x*cosB-shapeB->Gethalves().y*sinB,shapeB->Gethalves().y*cosB-shapeB->Gethalves().x*sinB),//Top Left
        B.position+glm::vec2(shapeB->Gethalves().x*cosB+shapeB->Gethalves().y*sinB,-shapeB->Gethalves().y*cosB+shapeB->Gethalves().x*sinB),//Bottom Right
        B.position+glm::vec2(-shapeB->Gethalves().x*cosB+shapeB->Gethalves().y*sinB,-shapeB->Gethalves().y*cosB-shapeB->Gethalves().x*sinB)//Bottom Left
    };
    std::pair<int,int> Faces[4] = {
        {0,1},// Top
        {2,0},// Right
        {1,3},// Left
        {3,2} // Bottom
    };
    
    int axisindex;
    float min_penetration = FLT_MAX;
    glm::vec2 normal;
    bool collision = true;
    for(int j = 0; j<4; j++){
        float minA = FLT_MAX;
        float maxA = -FLT_MAX;
        float minB = FLT_MAX;
        float maxB = -FLT_MAX;
        for(int i=0; i<4;i++){
            glm::vec2 a = CoordinatesA[i];
            glm::vec2 b = CoordinatesB[i];
            float projection =glm::dot(a,Axixes[j]);
            minA = std::min(projection,minA);
            maxA = std::max(projection,maxA);
            
            projection =glm::dot(b,Axixes[j]);
            minB = std::min(projection,minB);
            maxB = std::max(projection,maxB);
        }
        float overlap = std::min(maxA,maxB) - std::max(minA,minB);
        if(overlap<0) {
            collision = false;
            break;}
        if(min_penetration>overlap){
            min_penetration = overlap;
            normal = Axixes[j];
            axisindex = j;
            if(glm::dot(normal,(B.position-A.position))<0) normal = -normal;
        }
    }
    if(!collision) return{false};

    bool isAreference = axisindex < 2;
    glm::vec2* ReferenceCoords = isAreference? CoordinatesA : CoordinatesB;
    glm::vec2* IncidentCoords  = isAreference? CoordinatesB : CoordinatesA;

    normal = isAreference? normal : -normal;

    int reference_face=0;
    int incident_face =0;

    float Best_dotRef = -FLT_MAX;
    float Best_dotInc = FLT_MAX;

    for(int i = 0; i<4; i++){
        glm::vec2 normRef = ReferenceCoords[Faces[i].first]-ReferenceCoords[Faces[i].second];
        normRef = glm::vec2(-normRef.y,normRef.x);
        
        glm::vec2 normInc = IncidentCoords[Faces[i].first]-IncidentCoords[Faces[i].second];
        normInc = glm::vec2(-normInc.y,normInc.x);

        float dotRef = glm::dot(normal,normRef);
        float dotInc = glm::dot(normal,normInc);

        if(dotRef>Best_dotRef){
            Best_dotRef = dotRef;
            reference_face = i;
        }
        
        if(dotInc<Best_dotInc){
            Best_dotInc = dotInc;
            incident_face = i;
        }
    }

    glm::vec2 R1 =
        ReferenceCoords[Faces[reference_face].first];

    glm::vec2 R2 =
        ReferenceCoords[Faces[reference_face].second];

    glm::vec2 P1 =
        IncidentCoords[Faces[incident_face].first];

    glm::vec2 P2 =
        IncidentCoords[Faces[incident_face].second];
    
    glm::vec2 T = glm::normalize(R2 - R1);

    std::vector<glm::vec2> clippedPoints = { P1, P2 };

    constexpr float epsilon = 0.00001f;
    auto ClipSegment =
        [&epsilon](std::vector<glm::vec2>& points,
           const glm::vec2& planePoint,
           const glm::vec2& inwardNormal)
    {

        if (points.empty())
            return;

        if (points.size() == 1)
        {
            float d = glm::dot(
                inwardNormal, points[0] - planePoint);

            if (d < -epsilon)
                points.clear();

            return;
        }

        glm::vec2 A = points[0];
        glm::vec2 B = points[1];

        float dA = glm::dot(inwardNormal, A - planePoint);
        float dB = glm::dot(inwardNormal, B - planePoint);

        bool insideA = dA >= -epsilon;
        bool insideB = dB >= -epsilon;

        if (!insideA && !insideB)
        {
            points.clear();
            return;
        }

        if (insideA != insideB)
        {
            float t = dA / (dA - dB);
            glm::vec2 intersection = A + t * (B - A);

            if (!insideA)
                A = intersection;
            else
                B = intersection;
        }

        points.clear();
        points.push_back(A);
        points.push_back(B);
    };

    ClipSegment(clippedPoints, R1, T);
    ClipSegment(clippedPoints, R2, -T);


    std::vector<glm::vec2> contacts;

    for (const glm::vec2& p : clippedPoints)
    {
        float separation =
            glm::dot(normal, p - R1);

        if (separation <= epsilon)
            contacts.push_back(p);
    }

    ColliderResult res = {true,normal,min_penetration,A.position,B.position,std::move(contacts)};
    // res.halfextend1 = shapeA->Gethalves();
    // res.halfextend2 = shapeB->Gethalves();
    // res.rot1 = A.rotation;
    // res.rot2 = B.rotation;
    
    // res.ACoord1 = ReferenceCoords[Faces[reference_face].first];
    // res.ACoord2 = ReferenceCoords[Faces[reference_face].second];
    
    // res.BCoord1 = IncidentCoords[Faces[incident_face].first];
    // res.BCoord2 = IncidentCoords[Faces[incident_face].second];
    return res;


}