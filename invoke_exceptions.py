
class InvokeExcepction(Exception):
    def __init__(self,message):
        self.message = message

class NoMainException(InvokeExcepction):
    ''' can't find main '''
    def __init__(self,message):
        self.message = message

class BadData(InvokeExcepction):
    '''bad filename or bad function addresses '''
    def __init__(self,message):
        self.message = message
