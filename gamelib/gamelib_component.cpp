#include "pch.h"
#include <gamelib_random.hpp>
#include <gamelib_locator.hpp>
#include <gamelib_component.hpp>

namespace GameLib {
    void SimpleInputComponent::update(Actor& actor) {
        auto axis1 = Locator::getInput()->axis1X;
        if (axis1){
            actor.velocity.x = axis1->getAmount();
	}
        auto axis2 = Locator::getInput()->axis1Y;
        if (axis2)
            actor.velocity.y = axis2->getAmount();

	
    }

    void RandomInputComponent::update(Actor& actor) {
        actor.velocity.x = random.normal();
        actor.velocity.y = random.normal();
        glm::normalize(actor.velocity);
    }
    void MissileInputComponent::update(Actor& actor){
	    actor.velocity=glm::vec3(0.0,0.0,0.0);
	    if(actor.hp<5){
		actor.spriteId=3;
		actor.collide_dist=1.0;
	    }
	    actor.hp-=watch.Stop_sf()*0.0005;


    }

    void SimpleActorComponent::update(Actor& actor, World& world) {
        // We could make decisions here, start actions, etc
    }

	void RandomActorComponent::update(Actor& actor, World& world) {

        for (auto& a : world.actors) {
            if (a->getId() == actor.getId())
                continue;
            
        }
    }

    void SimplePhysicsComponent::update(Actor& actor, World& world) {
	    actor.position += actor.dt * actor.speed * actor.velocity;
	    auto act=world.actors[0];
	    for(auto& act:world.actors){
		    if(act->getId()==actor.getId())
		   	continue;
		    else{
			glm::vec3 vec = act->position-actor.position;
			float dist = glm::length(vec);
			if(dist<=act->collide_dist){
				actor.hp-=5.0;
			}
		    }

    	}
    }

    void SimpleGraphicsComponent::update(Actor& actor, Graphics& graphics) {
        glm::vec3 tileSize{ graphics.getTileSizeX(), graphics.getTileSizeY(), 0 };
        glm::vec3 pos = actor.position * tileSize;
        graphics.draw(actor.spriteLibId, actor.spriteId, pos.x, pos.y);
    }
}
