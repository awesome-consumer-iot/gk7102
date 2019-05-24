#ifndef __SLOT_H_
#define __SLOT_H_
#include <json-c/json.h>

#include "slot_sds.h"
#include "slot_sem.h"

/**
 * @brief slot_free �ͷŽ�������������ڴ�.
 * @param asr_info [in] �������ṹ��.
 */


extern void slot_free(asr_info_t *asr_info);
/**
 * @brief slot_resolve ��ȡ����ʶ��ķ��ؽ��.
 * @param sem_json [in] �����ԭʼjson.
 * @param asr_info [out] �������ṹ��.
 *
 * @return ���ؽ���� 0 �ɹ��� -1���쳣ʧ��.
 *
 * @details ʹ�ô˺���������ڴ棬���ں���ʹ��slot_free�����ͷŷ���Ŀռ�
 */

extern int slot_resolve(json_object *sem_json, asr_info_t *asr_info);


#endif

