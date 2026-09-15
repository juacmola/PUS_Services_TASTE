from functools import partial

import DV

from Stubs import (
    myassert, Clean, DataStream, COMMON)

class RawTC(COMMON):
    def __init__(self, ptr=None):
        super(RawTC, self).__init__("RawTC", ptr)
#

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        value = self.GetPyString(tryToDecodeAscii=False)
        value = "'" + value.hex().upper() + "'H"
        lines.append(""+value)

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class RxTC(COMMON):
    # Allowed enumerants:
    not_accepted = 0
    accepted = 1
    allowed = [not_accepted, accepted]
    def __init__(self, ptr=None):
        super(RxTC, self).__init__("RxTC", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+{'0': 'not-accepted', '1': 'accepted'}[str(self.Get())])

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class FwdCommand(COMMON):
    # Allowed enumerants:
    to_reboot = 0
    exec_prio_tc = 1
    fwdhk_fdir_tc = 2
    fwdbkgtc = 3
    allowed = [to_reboot, exec_prio_tc, fwdhk_fdir_tc, fwdbkgtc]
    def __init__(self, ptr=None):
        super(FwdCommand, self).__init__("FwdCommand", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+{'0': 'to-reboot', '1': 'exec-prio-tc', '2': 'fwdhk-fdir-tc', '3': 'fwdbkgtc'}[str(self.Get())])

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class GPendingEvAction(COMMON):
    def __init__(self, ptr=None):
        super(GPendingEvAction, self).__init__("GPendingEvAction", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+str(self.Get()!=0).upper())

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class GToReboot(COMMON):
    def __init__(self, ptr=None):
        super(GToReboot, self).__init__("GToReboot", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+str(self.Get()!=0).upper())

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class GFwToHK_FDIR(COMMON):
    def __init__(self, ptr=None):
        super(GFwToHK_FDIR, self).__init__("GFwToHK_FDIR", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+str(self.Get()!=0).upper())

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class GFwToBKG(COMMON):
    def __init__(self, ptr=None):
        super(GFwToBKG, self).__init__("GFwToBKG", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+str(self.Get()!=0).upper())

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class Telecommand(COMMON):
    # Ordered list of fields:
    children_ordered = ['service-type', 'subservice-type', 'param']

    def __init__(self, ptr=None):
        super(Telecommand, self).__init__("Telecommand", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append("{")
        lines.append("service-type ")
        lines.append(" "+str(self.service_type.Get()))
        lines.append(', ')
        lines.append("subservice-type ")
        lines.append(" "+str(self.subservice_type.Get()))
        lines.append(', ')
        lines.append("param ")
        value = self.param.GetPyString(tryToDecodeAscii=False)
        value = "'" + value.hex().upper() + "'H"
        lines.append(" "+value)
        lines.append("}")

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class Pr_time(COMMON):
    def __init__(self, ptr=None):
        super(Pr_time, self).__init__("Pr_time", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+str(self.Get()))

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class T_Int32(COMMON):
    def __init__(self, ptr=None):
        super(T_Int32, self).__init__("T_Int32", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+str(self.Get()))

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class T_UInt32(COMMON):
    def __init__(self, ptr=None):
        super(T_UInt32, self).__init__("T_UInt32", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+str(self.Get()))

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class T_Runtime_Error(COMMON):
    def __init__(self, ptr=None):
        super(T_Runtime_Error, self).__init__("T_Runtime_Error", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        if self.kind.Get() == DV.T_Runtime_Error_noerror_PRESENT:
         lines.append("noerror: ")
         lines.append(" "+str(self.noerror.Get()))
        if self.kind.Get() == DV.T_Runtime_Error_encodeerror_PRESENT:
         lines.append("encodeerror: ")
         lines.append(" "+str(self.encodeerror.Get()))
        if self.kind.Get() == DV.T_Runtime_Error_decodeerror_PRESENT:
         lines.append("decodeerror: ")
         lines.append(" "+str(self.decodeerror.Get()))

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class T_Int8(COMMON):
    def __init__(self, ptr=None):
        super(T_Int8, self).__init__("T_Int8", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+str(self.Get()))

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class T_UInt8(COMMON):
    def __init__(self, ptr=None):
        super(T_UInt8, self).__init__("T_UInt8", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+str(self.Get()))

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class T_Boolean(COMMON):
    def __init__(self, ptr=None):
        super(T_Boolean, self).__init__("T_Boolean", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+str(self.Get()!=0).upper())

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class T_Null_Record(COMMON):
    # Ordered list of fields:
    children_ordered = ['']

    def __init__(self, ptr=None):
        super(T_Null_Record, self).__init__("T_Null_Record", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append("{")
        lines.append("}")

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class PID_Range(COMMON):
    def __init__(self, ptr=None):
        super(PID_Range, self).__init__("PID_Range", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+str(self.Get()))

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


class PID(COMMON):
    # Allowed enumerants:
    bkgtcexec = 0
    hkfdirmng = 1
    irq = 2
    legacy = 3
    tcmanager = 4
    env = 5
    allowed = [bkgtcexec, hkfdirmng, irq, legacy, tcmanager, env]
    def __init__(self, ptr=None):
        super(PID, self).__init__("PID", ptr)

    def GSER(self):
        ''' Return the GSER representation of the value '''
        lines = []
        lines.append(""+{'0': 'bkgtcexec', '1': 'hkfdirmng', '2': 'irq', '3': 'legacy', '4': 'tcmanager', '5': 'env'}[str(self.Get())])

        return ' '.join(lines)

    def PrintAll(self):
        ''' Display a variable of this type '''
        print(self.GSER() + '\n')


