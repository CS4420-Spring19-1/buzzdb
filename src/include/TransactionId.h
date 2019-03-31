/*
import java.io.Serializable;
import java.util.concurrent.atomic.AtomicLong;
*/

namespace emerald{
    class TransactionId{
      private:
        long myid;
        void TransactionId(long myid) {this.myid = myid;};
      public:
        void TransactionId() { /*myid = counter.getAndIncrement(); */ };
        long getId() {return myid;};
        bool equals(void* o);
        int hashCode() {return (int)myid;};
    }
}