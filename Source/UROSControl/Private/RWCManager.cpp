// Copyright 2017-2019, Institute for Artificial Intelligence - University of Bremen

#include "RWCManager.h"
#include "SpawnModelsServer.h"
#include "SetModelPoseServer.h"
#include "GetModelPoseServer.h"
#include "RemoveModelServer.h"
#include "AttachModelToParentServer.h"
#include "SpawnPhysicsConstraintServer.h"
#include "HighlightModelsServer.h"
#include "SetPhysicsPropertiesServer.h"
#include "SetMaterialServer.h"
#include "SpawnSemanticMapServer.h"
#include "SpawnRobotServer.h"

void URWCManager::Register(FString DefaultNamespace)
{
	Namespace = DefaultNamespace;

	if (!GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s]: GetWorld returned, NULL."), *FString(__FUNCTION__));
		return;
	}

	SetupServiceServers();
}


void URWCManager::SetupServiceServers()
{
	// Add Service Servers
	UWorld* World = GetWorld();

	ServicesToPublish.Add(MakeShareable<FROSSpawnModelServer>(new FROSSpawnModelServer(Namespace, TEXT("spawn_model"), World, this)));
	ServicesToPublish.Add(MakeShareable<FROSSetModelPoseServer>(new FROSSetModelPoseServer(Namespace, TEXT("set_model_pose"), World, this)));
	ServicesToPublish.Add(MakeShareable<FROSGetModelPoseServer>(new FROSGetModelPoseServer(Namespace, TEXT("get_model_pose"), World, this)));
	ServicesToPublish.Add(MakeShareable<FROSRemoveModelServer>(new FROSRemoveModelServer(Namespace, TEXT("delete_model"), World, this)));
	ServicesToPublish.Add(MakeShareable<FROSAttachModelToParentServer>(new FROSAttachModelToParentServer(Namespace, TEXT("attach_model_to_parent"), World, this)));
	ServicesToPublish.Add(MakeShareable<FROSSpawnPhysicsConstraintServer>(new FROSSpawnPhysicsConstraintServer(Namespace, TEXT("spawn_physics_constraint"), World, this)));
	ServicesToPublish.Add(MakeShareable<FROSHighlightModelsServer>(new FROSHighlightModelsServer(Namespace, TEXT("highlight_models"), World, this)));
	ServicesToPublish.Add(MakeShareable<FROSSetPhysicsPropertiesServer>(new FROSSetPhysicsPropertiesServer(Namespace, TEXT("set_physics_properties"), World, this)));
	ServicesToPublish.Add(MakeShareable<FROSSetMaterialServer>(new FROSSetMaterialServer(Namespace, TEXT("change_material"), World, this)));
    ServicesToPublish.Add(MakeShareable<FROSSpawnSemanticMapServer>(new FROSSpawnSemanticMapServer(Namespace, TEXT("spawn_semantic_map"), World, this)));
    ServicesToPublish.Add(MakeShareable<FROSSpawnRobotServer>(new FROSSpawnRobotServer(Namespace, TEXT("spawn_robot"), World, this)));

}
