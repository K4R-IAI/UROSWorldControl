#pragma once
#include "ROSBridgeSrv.h"
#include "Pose.h"
#include "Tag.h"
#include "PhysicsProperties.h"




class UROSBRIDGE_API FROSSpawnModelSrv : public FROSBridgeSrv
{
protected:
	FString Type;

public:
	FROSSpawnModelSrv(FString InType)
	{
		Type = InType;
	}

	class Request : public SrvRequest
	{
	private:
		FString Name;
		geometry_msgs::Pose Pose;
		FString Id;
		TArray<world_control_msgs::Tag> Tags;
		FString Path;
		FString ActorLabel;
		world_control_msgs::PhysicsProperties PhysicsProperties;
		TArray<FString> MaterialNames;
		TArray<FString> MaterialPaths;
		FString ParentId;


	public:
		Request() {}

		Request(FString InName, geometry_msgs::Pose InPose, FString InId, TArray<world_control_msgs::Tag> InTags, FString InPath, FString InActorLabel, world_control_msgs::PhysicsProperties InPhysicsProperties, TArray<FString> InMaterialNames, TArray<FString> InMaterialPaths, FString InParentId)
		{
			Name = InName;
			Pose = InPose;
			Id = InId;
			Tags = InTags;
			Path = InPath;
			ActorLabel = InActorLabel;
			PhysicsProperties = InPhysicsProperties;
			MaterialNames = InMaterialNames;
			MaterialPaths = InMaterialPaths;
			ParentId = InParentId;
		}

		FString GetName()
		{
			return Name;
		}

		geometry_msgs::Pose GetPose()
		{
			return Pose;
		}

		FString GetId()
		{
			return Id;
		}

		TArray<world_control_msgs::Tag> GetTags()
		{
			return Tags;
		}

		FString GetPath()
		{
			return Path;
		}

		FString GetActorLabel()
		{
			return ActorLabel;
		}

		world_control_msgs::PhysicsProperties GetPhysicsProperties()
		{
			return PhysicsProperties;
		}

		TArray<FString> GetMaterialNames()
		{
			return MaterialNames;
		}

		TArray<FString> GetMaterialPaths()
		{
			return MaterialPaths;
		}

		FString GetParentId()
		{
			return ParentId;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Name = JsonObject->GetStringField("name");
			Pose.FromJson(JsonObject->GetObjectField("pose"));
			Id = JsonObject->GetStringField("id");
			Tags.Empty();
			TArray<TSharedPtr<FJsonValue>> TagsPtrArray = JsonObject->GetArrayField(TEXT("tags"));
			for (auto &ptr : TagsPtrArray)
			{
				world_control_msgs::Tag Entry;
				Entry.FromJson(ptr->AsObject());
				Tags.Add(Entry);
			}

			Path = JsonObject->GetStringField("path");
			ActorLabel = JsonObject->GetStringField("actor_label");
			PhysicsProperties.FromJson(JsonObject->GetObjectField("physics_properties"));
			MaterialNames.Empty();
			TArray<TSharedPtr<FJsonValue>> MaterialNamesPtrArray = JsonObject->GetArrayField(TEXT("material_names"));
			for (auto &ptr : MaterialNamesPtrArray)
			{
				FString Entry = ptr->AsString();
				MaterialNames.Add(Entry);
			}

			MaterialPaths.Empty();
			TArray<TSharedPtr<FJsonValue>> MaterialPathsPtrArray = JsonObject->GetArrayField(TEXT("material_paths"));
			for (auto &ptr : MaterialPathsPtrArray)
			{
				FString Entry = ptr->AsString();
				MaterialPaths.Add(Entry);
			}

			ParentId = JsonObject->GetStringField("parent_id");
		}

		static Request GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Request Req;
			Req.FromJson(JsonObject);
			return Req;
		}

		FString ToString() const override
		{
			return TEXT("FROSSpawnModelSrv:Request {name = %s, pose = %s, id = %s, tags size = %s, path = %s, actor_label = %s, physics_properties = %s, material_names size = %s, material_paths size = %s, parent_id = %s"),
				Name,
				Pose.ToString(),
				Id,
				FString::FromInt(Tags.Num()),
				Path,
				ActorLabel,
				PhysicsProperties.ToString(),
				FString::FromInt(MaterialNames.Num()),
				FString::FromInt(MaterialPaths.Num()),
				ParentId;
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetStringField(TEXT("name"), Name);
			Object->SetObjectField(TEXT("pose"), Pose.ToJsonObject());
			Object->SetStringField(TEXT("id"), Id);
			TArray<TSharedPtr<FJsonValue>> TagsPtrArray;
			for (auto &Entry : Tags)
			{
				TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueObject(Entry.ToJsonObject()));
				TagsPtrArray.Add(Ptr);
			}
			Object->SetArrayField("tags", TagsPtrArray);

			Object->SetStringField(TEXT("path"), Path);
			Object->SetStringField(TEXT("actor_label"), ActorLabel);
			Object->SetObjectField(TEXT("physics_properties"), PhysicsProperties.ToJsonObject());
			TArray<TSharedPtr<FJsonValue>> MaterialNamesPtrArray;
			for (auto &Entry : MaterialNames)
			{
				TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueString(Entry));
				MaterialNamesPtrArray.Add(Ptr);
			}
			Object->SetArrayField("material_names", MaterialNamesPtrArray);

			TArray<TSharedPtr<FJsonValue>> MaterialPathsPtrArray;
			for (auto &Entry : MaterialPaths)
			{
				TSharedPtr<FJsonValue> Ptr = MakeShareable(new FJsonValueString(Entry));
				MaterialPathsPtrArray.Add(Ptr);
			}
			Object->SetArrayField("material_paths", MaterialPathsPtrArray);

			Object->SetStringField(TEXT("parent_id"), ParentId);
			return Object;
		}

	};

	class Response : public SrvResponse
	{
	private:
		FString Id;
		bool Success;


	public:
		Response() {}

		Response(FString InId, bool InSuccess)
		{
			Id = InId;
			Success = InSuccess;
		}

		FString GetId()
		{
			return Id;
		}

		bool GetSuccess()
		{
			return Success;
		}

		virtual void FromJson(TSharedPtr<FJsonObject> JsonObject) override
		{
			Id = JsonObject->GetStringField("id");
			Success = JsonObject->GetBoolField("success");
		}

		static Response GetFromJson(TSharedPtr<FJsonObject> JsonObject)
		{
			Response Res;
			Res.FromJson(JsonObject);
			return Res;
		}

		FString ToString() const override
		{
			return TEXT("FROSSpawnModelSrv:Response {id = %s, success = %s"),
				Id,
				Success ? TEXT("True") : TEXT("False");
		}

		virtual TSharedPtr<FJsonObject> ToJsonObject() const override
		{
			TSharedPtr<FJsonObject> Object = MakeShareable<FJsonObject>(new FJsonObject());
			Object->SetStringField(TEXT("id"), Id);
			Object->SetBoolField(TEXT("success"), Success);
			return Object;
		}

	};

};