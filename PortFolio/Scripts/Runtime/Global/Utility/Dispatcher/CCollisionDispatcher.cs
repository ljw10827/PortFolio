using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//! 충돌 이벤트 디스패처 
public class CCollisionDispatcher : CComponent
{
	public System.Action<GameObject, Collision> CollisionEnter { get; set; }
	public System.Action<GameObject, Collision> CollisionStay { get; set; }
	public System.Action<GameObject, Collision> CollisionExit { get; set; }

	//! 충돌이 발생했을 경우
	public void OnCollisionEnter(Collision a_oCollision)
	{
		if (this.CollisionEnter != null)
		{
			this.CollisionEnter(this.gameObject, a_oCollision);
		}
	}

	//! 충돌 중일 경우
	public void OnCollisionStay(Collision a_oCollision)
	{
		if (this.CollisionStay != null)
		{
			this.CollisionStay(this.gameObject, a_oCollision);
		}
	}

	//! 충돌이 끝났을 경우
	public void OnCollisionExit(Collision a_oCollsion)
	{
		if (this.CollisionExit != null)
		{
			this.CollisionExit(this.gameObject, a_oCollsion);
		}
	}
}
