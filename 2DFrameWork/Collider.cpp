#include "framework.h"

Collider::Collider(ColliderType type)
{
	this->type = type;
	visible = true;
	switch (type)
	{
	case ColliderType::SPHERE:
		mesh = RESOURCE->meshes.Load("1.SphereCollider.mesh");
		break;
	case ColliderType::BOX:
		mesh = RESOURCE->meshes.Load("1.BoxCollider.mesh");
		break;
	case ColliderType::OBOX:
		mesh = RESOURCE->meshes.Load("1.BoxCollider.mesh");
		break;
	}
	shader = RESOURCE->shaders.Load("1.Collider.hlsl");
}

Collider::~Collider()
{
	SafeReset(mesh);
	SafeReset(shader);
}

void Collider::Update(GameObject* ob)
{
	parent = ob;
	/*if (type == ColliderType::SPHERE)
	{
		scale.z = scale.y = scale.x;
	}*/
	Transform::Update();
	if (type == ColliderType::BOX)
	{
		T = Matrix::CreateTranslation(GetWorldPos());
		W = S * T;
	}
	if (type == ColliderType::SPHERE)
	{
		scale.z = scale.y = scale.x;
		S = Matrix::CreateScale(scale.x);
		T = Matrix::CreateTranslation(GetWorldPos());
		W = S * T;
	}


}

void Collider::Render()
{

	if (visible)
	{
		Transform::Set();
		mesh->Set();
		shader->Set();
		mesh->DrawCall();
	}
}


bool Collider::Intersect(Collider* target)
{
	if (type == ColliderType::BOX)
	{
		BoundingBox box1;
		box1.Center = GetWorldPos();
		box1.Extents = Vector3(S._11, S._22, S._33);
		if (target->type == ColliderType::BOX)
		{
			BoundingBox box2;
			box2.Center = target->GetWorldPos();
			box2.Extents = Vector3(target->S._11, target->S._22, target->S._33);
			return box1.Intersects(box2);
		}
		else if (target->type == ColliderType::OBOX)
		{
			BoundingOrientedBox box2;
			box2.Center = target->GetWorldPos();
			box2.Extents = Vector3(target->S._11, target->S._22, target->S._33);
			box2.Orientation = Quaternion::CreateFromRotationMatrix(target->RT);
			return box1.Intersects(box2);
		}
		else
		{
			BoundingSphere box2;
			box2.Center = target->GetWorldPos();
			box2.Radius = target->scale.x;
			return box1.Intersects(box2);
		}
	}
	else if (type == ColliderType::OBOX)
	{
		BoundingOrientedBox box1;
		box1.Center = GetWorldPos();
		box1.Extents = Vector3(S._11, S._22, S._33);
		box1.Orientation = Quaternion::CreateFromRotationMatrix(RT);
		if (target->type == ColliderType::BOX)
		{
			BoundingBox box2;
			box2.Center = target->GetWorldPos();
			box2.Extents = Vector3(target->S._11, target->S._22, target->S._33);
			return box1.Intersects(box2);
		}
		else if (target->type == ColliderType::OBOX)
		{
			BoundingOrientedBox box2;
			box2.Center = target->GetWorldPos();
			box2.Extents = Vector3(target->S._11, target->S._22, target->S._33);
			box2.Orientation = Quaternion::CreateFromRotationMatrix(target->RT);
			return box1.Intersects(box2);
		}
		else
		{
			BoundingSphere box2;
			box2.Center = target->GetWorldPos();
			box2.Radius = target->scale.x;
			return box1.Intersects(box2);
		}
	}
	else
	{
		BoundingSphere box1;
		box1.Center = GetWorldPos();
		box1.Radius = scale.x;
		if (target->type == ColliderType::BOX)
		{
			BoundingBox box2;
			box2.Center = target->GetWorldPos();
			box2.Extents = Vector3(target->S._11, target->S._22, target->S._33);
			return box1.Intersects(box2);
		}
		else if (target->type == ColliderType::OBOX)
		{
			BoundingOrientedBox box2;
			box2.Center = target->GetWorldPos();
			box2.Extents = Vector3(target->S._11, target->S._22, target->S._33);
			box2.Orientation = Quaternion::CreateFromRotationMatrix(target->RT);
			return box1.Intersects(box2);
		}
		else
		{
			BoundingSphere box2;
			box2.Center = target->GetWorldPos();
			box2.Radius = target->scale.x;
			return box1.Intersects(box2);
		}
	}
	return false;
}

bool Collider::Intersect(Vector3 coord)
{
	float Dis;
	bool result = false;
	if (type == ColliderType::BOX)
	{
		BoundingBox box1;
		box1.Center = GetWorldPos();
		box1.Extents = Vector3(S._11, S._22, S._33);

		//XMVECTOR temp = XMLoadFloat3(&coord);
		result = box1.Contains(coord) >= INTERSECTS;
	}
	else if (type == ColliderType::OBOX)
	{
		BoundingBox box1;
		box1.Center = Vector3(0, 0, 0);
		box1.Extents = Vector3(S._11, S._22, S._33);
		Matrix inverse = S.Invert() * W;
		inverse = inverse.Invert();

		coord = Vector3::Transform(coord, inverse);
		result = box1.Contains(coord) >= INTERSECTS;
	}
	else
	{
		BoundingSphere box1;
		box1.Center = GetWorldPos();
		box1.Radius = scale.x;
		result = box1.Contains(coord) >= INTERSECTS;
	}
	return result;
}

bool Collider::Intersect(Ray Ray, Vector3& Hit)
{
	Ray.direction.Normalize();
	float Dis;
	bool result = false;
	if (type == ColliderType::BOX)
	{
		BoundingBox box1;
		box1.Center = GetWorldPos();
		box1.Extents = Vector3(S._11, S._22, S._33);
		result = Ray.Intersects(box1, Dis);
		Hit = Ray.position + Ray.direction * Dis;
	}
	else if (type == ColliderType::OBOX)
	{
		BoundingBox box1;
		box1.Center = Vector3(0, 0, 0);
		box1.Extents = Vector3(S._11, S._22, S._33);
		Matrix inverse = S.Invert() * W;
		inverse = inverse.Invert();
		Ray.position = Vector3::Transform(Ray.position, inverse);
		Ray.direction = Vector3::TransformNormal(Ray.direction, inverse);
		Ray.direction.Normalize();


		result = Ray.Intersects(box1, Dis);
		Hit = Ray.position + Ray.direction * Dis;
		Hit = Vector3::Transform(Hit, inverse.Invert());
	}
	else
	{
		BoundingSphere box1;
		box1.Center = GetWorldPos();
		box1.Radius = scale.x;
		result = Ray.Intersects(box1, Dis);
		Hit = Ray.position + Ray.direction * Dis;
	}

	return result;
}

Vector3 Collider::GetNormalVector(const Vector3 collisionPoint)
{
	// BOX 타입 콜라이더에 대한 정규 벡터 계산
	if (type == ColliderType::BOX)
	{
		// 충돌점과 콜라이더 중심점 사이의 차이 계산
		Vector3 diff = this->GetWorldPos() - collisionPoint;
		diff.Normalize();

		// 각 면의 정규 벡터와 내적 계산
		float dotForward = this->GetForward().Dot(diff);
		float dotRight = this->GetRight().Dot(diff);

		// 모서리에서의 충돌 특별 처리
		// 내적 값이 0.5 또는 -0.5에 가까운 경우 모서리 충돌로 간주
		if ((std::abs(dotForward) > 0.5f || std::abs(dotForward) < -0.5f) &&
			(std::abs(dotRight) > 0.5f || std::abs(dotRight) < -0.5f))
		{
			Vector3 averageNormal = Vector3::Zero;
			if (dotForward > 0.5f) averageNormal += this->GetForward();
			else if (dotForward < -0.5f) averageNormal -= this->GetForward();

			if (dotRight > 0.5f) averageNormal += this->GetRight();
			else if (dotRight < -0.5f) averageNormal -= this->GetRight();

			averageNormal.Normalize();
			return averageNormal;
		}

		// 일반 면 충돌 처리
		if (dotForward > 0.5f)
			return this->GetForward();
		else if (dotForward < -0.5f)
			return -this->GetForward();
		else if (dotRight > 0.5f)
			return this->GetRight();
		else
			return -this->GetRight();
	}
	// OBOX 타입 콜라이더에 대한 정규 벡터 계산
	else if (type == ColliderType::OBOX)
	{
	}
	// SPHERE 타입 콜라이더에 대한 정규 벡터 계산
	else if (type == ColliderType::SPHERE)
	{

	}
}