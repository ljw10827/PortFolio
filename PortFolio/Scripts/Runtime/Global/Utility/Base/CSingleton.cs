using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//! 싱글턴
public class CSingleton<T> : CComponent where T : CComponent
{
    private static T m_tInstance = null;

    //! 인스턴스 프로퍼티
    public static T Instance
    {
        get
        {
            if (m_tInstance == null)
            {
                var oGameObject = new GameObject(typeof(T).ToString());
                m_tInstance = oGameObject.AddComponent<T>();

                DontDestroyOnLoad(oGameObject);
            }

            return m_tInstance;
        }
    }

    //! 인스턴스를 생성한다
    public static T Create()
    {
        return CSingleton<T>.Instance;
    }
}
