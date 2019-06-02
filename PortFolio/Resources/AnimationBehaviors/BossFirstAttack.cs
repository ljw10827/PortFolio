using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossFirstAttack : StateMachineBehaviour {

	 // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
	//override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {
	//
	//}

	// OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
	//override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {
	//
	//}

	// OnStateExit is called when a transition ends and the state machine finishes evaluating this state
	override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {
		var oCharacters = CSceneManager.ObjectRoot.transform.Find("Characters");
		var oController = oCharacters.gameObject.GetComponent<CBossController>();
		var oEnemy = animator.gameObject.GetComponent<CBoss>();

		int nRandomSkill = Random.Range(0, 2);

		if(nRandomSkill == 0)
		{
			var oSkill = Function.CreateCopiedGameObject("Explosion", "Prefabs/BattleObject/Explosion1", CSceneManager.ObjectRoot);
			oSkill.transform.localPosition = new Vector3(-77.0f, 138.0f, 0.0f);

			Function.LateCall((a_oParams) =>
			{
				if (!oController.m_bIsAttack)
				{
					var oRotation = animator.gameObject.transform.localRotation;
					oRotation.y = 180.0f;
					animator.gameObject.transform.Rotate(0.0f, oRotation.y, 0.0f);

					oEnemy.m_bAttackEnable = false;
					oController.PlayerAllDamage(oEnemy.DamageCalculate());
					oController.ReturnEnemy(oEnemy);
				}
			}, 5.5f);
		}

		else
		{
			var oSkill = Function.CreateCopiedGameObject("Explosion", "Prefabs/BattleObject/Explosion2", CSceneManager.ObjectRoot);
			oSkill.transform.localPosition = new Vector3(-77.0f, 138.0f, 0.0f);

			Function.LateCall((a_oParams) =>
			{
				if (!oController.m_bIsAttack)
				{
					var oRotation = animator.gameObject.transform.localRotation;
					oRotation.y = 180.0f;
					animator.gameObject.transform.Rotate(0.0f, oRotation.y, 0.0f);

					oEnemy.m_bAttackEnable = false;
					oController.PlayerAllDamage(oEnemy.DamageCalculate());
					oController.ReturnEnemy(oEnemy);
				}
			}, 7.0f);
		}
	}

	// OnStateMove is called right after Animator.OnAnimatorMove(). Code that processes and affects root motion should be implemented here
	//override public void OnStateMove(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {
	//
	//}

	// OnStateIK is called right after Animator.OnAnimatorIK(). Code that sets up animation IK (inverse kinematics) should be implemented here.
	//override public void OnStateIK(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {
	//
	//}
}
