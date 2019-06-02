using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyFirstAttack : StateMachineBehaviour {

	 // OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
	//override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {
	//
	//}

	// OnStateUpdate is called on each Update frame between OnStateEnter and OnStateExit callbacks
	//override public void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {
	//}

	// OnStateExit is called when a transition ends and the state machine finishes evaluating this state
	override public void OnStateExit(Animator animator, AnimatorStateInfo stateInfo, int layerIndex) {

		var oCharacters = CSceneManager.ObjectRoot.transform.Find("Characters");
		var oController = oCharacters.gameObject.GetComponent<CController>();
		var oEnemy = animator.gameObject.GetComponent<CEnemy>();

		if (!oController.m_bIsAttack)
		{
			var oRotation = animator.gameObject.transform.localRotation;
			oRotation.y = 180.0f;
			animator.gameObject.transform.Rotate(0.0f, oRotation.y, 0.0f);

			oEnemy.m_bAttackEnable = false;
			oController.ReturnEnemy(oEnemy);
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
