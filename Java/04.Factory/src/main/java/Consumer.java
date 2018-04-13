class Consumer implements Runnable{
    Store _store;

    Consumer(Store store){
        _store = store;
    }

    public void run(){
        for (int i = 1; i < 6; i++) {
            _store.get();
        }
    }
}