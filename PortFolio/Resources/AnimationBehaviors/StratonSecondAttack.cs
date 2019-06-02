using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class StratonSecondAttack : StateMachineBehaviour {

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
		var nIndex = SceneManager.GetActiveScene().buildIndex;

		if (nIndex != 5)
		{
			var oParent = animator.transform.parent;
			var oController = oParent.GetComponent<CController>();
			var oPlayer = animator.gameObject.GetComponent<CPlayer>();


			if (!oController.m_bIsAttack)
			{
				var oRotation = animator.gameObject.transform.localRotation;
				oRotation.y = 180.0f;
				animator.gameObject.transform.Rotate(0.0f, oRotation.y, 0.0f);


				oController.ReturnPlayer(oPlayer);
			}
		}

		else if (nIndex == 5)
		{
			var oParent = animator.transform.parent;
			var oController = oParent.GetComponent<CBossController>();
			var oPlayer = animator.gameObject.GetComponent<CPlayer>();


			if (!oController.m_bIsAttack)
			{
				var oRotation = animator.gameObject.transform.localRotation;
				oRotation.y = 180.0f;
				animator.gameObject.transform.Rotate(0.0f, oRotation.y, 0.0f);


				oController.ReturnPlayer(oPlayer);
			}
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
