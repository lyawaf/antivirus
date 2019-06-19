
class InvokeException(Exception):
    def __init__(self,message):
        self.message = message

class NoMainException(InvokeException):
    ''' can't find main '''
    def __init__(self,message):
        self.message = message

class BadData(InvokeException):
    '''bad filename or bad function addresses '''
    def __init__(self,message):
        self.message = message
