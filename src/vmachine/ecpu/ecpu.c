//////////////////////////////////////////////////////////////////////////
// 名称	：CPU.cpp
// 功能	：模拟CPU
// 日期	：2008年4月20日
// 作者	：梁一信
//////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "memory.h"

#include "../vapi.h"
#include "../vcpuins.h"
#include "../vpic.h"
#include "ecpu.h"
#include "ecpuins.h"

t_ecpu ecpu;
static t_ecpu ecpu2;
static t_cpu  vcpu2;

void ecpuapiSyncRegs()
{
	ecpu.flagignore = 0;
	ecpu.ax = _ax;
	ecpu.bx = _bx;
	ecpu.cx = _cx;
	ecpu.dx = _dx;
	ecpu.sp = _sp;
	ecpu.bp = _bp;
	ecpu.si = _si;
	ecpu.di = _di;
	ecpu.ip = _ip;
	ecpu.cs = _cs;
	ecpu.ds = _ds;
	ecpu.es = _es;
	ecpu.ss = _ss;
	ecpu.flags = _flags;
	evIP = (ecpu.cs << 4) + ecpu.ip;
}
t_bool ecpuapiHasDiff()
{
	t_bool flagdiff = 0x00;
	t_nubit16 mask = GetMax16(vcpuins.udf);
	ecpu.flagignore |= vcpuins.flagrespondint;
	if (!ecpu.flagignore) {
		if (ecpu.ax != _ax) {vapiPrint("diff ax\n");flagdiff = 0x01;}
		if (ecpu.bx != _bx) {vapiPrint("diff bx\n");flagdiff = 0x01;}
		if (ecpu.cx != _cx) {vapiPrint("diff cx\n");flagdiff = 0x01;}
		if (ecpu.dx != _dx) {vapiPrint("diff dx\n");flagdiff = 0x01;}
		if (ecpu.sp != _sp) {vapiPrint("diff sp\n");flagdiff = 0x01;}
		if (ecpu.bp != _bp) {vapiPrint("diff bp\n");flagdiff = 0x01;}
		if (ecpu.si != _si) {vapiPrint("diff si\n");flagdiff = 0x01;}
		if (ecpu.di != _di) {vapiPrint("diff di\n");flagdiff = 0x01;}
		if (ecpu.ip != _ip) {vapiPrint("diff ip\n");flagdiff = 0x01;}
		if (ecpu.cs != _cs) {vapiPrint("diff cs\n");flagdiff = 0x01;}
		if (ecpu.ds != _ds) {vapiPrint("diff ds\n");flagdiff = 0x01;}
		if (ecpu.es != _es) {vapiPrint("diff es\n");flagdiff = 0x01;}
		if (ecpu.ss != _ss) {vapiPrint("diff ss\n");flagdiff = 0x01;}
		if ((ecpu.flags & ~mask) != (_flags & ~mask)) {
			vapiPrint("diff flags: E: %04X, V: %04X\n", ecpu.flags, _flags);
			flagdiff = 0x01;
		}
	}
	if (flagdiff) {
		vapiPrint("AFTER EXECUTION:\nVCPU REGISTERS\n");
		vapiCallBackDebugPrintRegs();
		ecpuapiPrintRegs();
		vapiPrint("BEFORE EXECUTION:\nVCPU REGISTERS\n");
		ecpu = ecpu2;
		vcpu = vcpu2;
		vapiCallBackDebugPrintRegs();
		ecpuapiPrintRegs();
	}
	return flagdiff;
}
void ecpuapiPrintRegs()
{
	vapiPrint("ECPU REGISTERS\n");
	vapiPrint(  "AX=%04X", ecpu.ax);
	vapiPrint("  BX=%04X", ecpu.bx);
	vapiPrint("  CX=%04X", ecpu.cx);
	vapiPrint("  DX=%04X", ecpu.dx);
	vapiPrint("  SP=%04X", ecpu.sp);
	vapiPrint("  BP=%04X", ecpu.bp);
	vapiPrint("  SI=%04X", ecpu.si);
	vapiPrint("  DI=%04X", ecpu.di);
	vapiPrint("\nDS=%04X", ecpu.ds);
	vapiPrint("  ES=%04X", ecpu.es);
	vapiPrint("  SS=%04X", ecpu.ss);
	vapiPrint("  CS=%04X", ecpu.cs);
	vapiPrint("  IP=%04X", ecpu.ip);
	vapiPrint("   ");
	if(ecpu.flags & VCPU_EFLAGS_OF) vapiPrint("OV ");
	else                            vapiPrint("NV ");
	if(ecpu.flags & VCPU_EFLAGS_DF) vapiPrint("DN ");
	else                            vapiPrint("UP ");
	if(ecpu.flags & VCPU_EFLAGS_IF) vapiPrint("EI ");
	else                            vapiPrint("DI ");
	if(ecpu.flags & VCPU_EFLAGS_SF) vapiPrint("NG ");
	else                            vapiPrint("PL ");
	if(ecpu.flags & VCPU_EFLAGS_ZF) vapiPrint("ZR ");
	else                            vapiPrint("NZ ");
	if(ecpu.flags & VCPU_EFLAGS_AF) vapiPrint("AC ");
	else                            vapiPrint("NA ");
	if(ecpu.flags & VCPU_EFLAGS_PF) vapiPrint("PE ");
	else                            vapiPrint("PO ");
	if(ecpu.flags & VCPU_EFLAGS_CF) vapiPrint("CY ");
	else                            vapiPrint("NC ");
	vapiPrint("\n");
}

t_bool ecpuapiScanINTR()
{
	return vpicScanINTR();
}
t_nubit8 ecpuapiGetINTR()
{
#if (VGLOBAL_ECPU_MODE == TEST_ECPU)
	return vpicGetINTR();
#else
	return vpicPeekINTR();
#endif
}

void ecpuInit()
{
#if (VGLOBAL_ECPU_MODE == TEST_VCPU)
	vcpuInit();
#elif (VGLOBAL_ECPU_MODE == TEST_ECPU)
	ecpuinsInit();
	vport.in[0xffff] = (t_faddrcc)ecpuapiPrintRegs;
#else
	ecpuinsInit();
	vcpuInit();
	vport.in[0xffff] = (t_faddrcc)ecpuapiPrintRegs;
#endif
}
void ecpuReset()
{
#if (VGLOBAL_ECPU_MODE == TEST_VCPU)
	vcpuReset();
#elif (VGLOBAL_ECPU_MODE == TEST_ECPU)
	memset(&ecpu,0,sizeof(t_ecpu));
	ecpu.cs = 0xf000;
	ecpu.ip = 0xfff0;
	evIP = (ecpu.cs << 4) + ecpu.ip;
#else
	vcpuReset();
	memset(&ecpu,0,sizeof(t_ecpu));
	ecpu.cs = 0xf000;
	ecpu.ip = 0xfff0;
	evIP = (ecpu.cs << 4) + ecpu.ip;
#endif
}
void ecpuRefresh()
{
#if (VGLOBAL_ECPU_MODE == TEST_VCPU)
	vcpuRefresh();
#elif (VGLOBAL_ECPU_MODE == TEST_ECPU)
	ecpuinsRefresh();
#else
	ecpuapiSyncRegs();
	vcpu2 = vcpu;
	ecpu2 = ecpu;
	ecpuinsRefresh();
	vcpuRefresh();
	if (ecpuapiHasDiff())
		vapiCallBackMachineStop();
#endif
}
void ecpuFinal()
{
#if (VGLOBAL_ECPU_MODE == TEST_VCPU)
	vcpuFinal();
#elif (VGLOBAL_ECPU_MODE == TEST_ECPU)
	ecpuinsFinal();
#else
	vcpuFinal();
	ecpuinsFinal();
#endif
}
