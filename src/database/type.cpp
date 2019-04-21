#include "type.h"
#include "integer_field.h"
#include "string_field.h"


namespace buzzdb {
int Type::get_length(FieldType field) {
  switch (field)
  {
    case INTEGER:
      return 4;
    case STRING:
      return STRING_LEN+4;
    default:
      break;
  }
}

// Field* Type::Parse(FieldType field, std::istringstream dis) {
//   switch (field)
//   {
//     case INTEGER:
//       try {
//         int val;
//         if (dis >> val) {
//           return new IntegerField(val);
//         }
//       } catch {
//         // throw new ParseException("cound not parse", 0);
//       }
//       break;
//     case STRING:
//       try {
//         int strLen;
//         dis >> strLen;
//         // follow https://stackoverflow.com/questions/5585532/c-int-to-byte-array/5585683
//         std::vector<unsigned char> arrayOfByte(strLen);
//         for (int i=0; i < strLen; i++) {
//           arrayOfByte[strLen-1-i] = (strLen >> (i*8));
//         }
//         // something wrong here actually
//         /*
//          * byte bs[] = new byte[strLen];
//          * dis.read(bs);
//          * dis.skipBytes(STRING_LEN - strlen);
//          * return new StringField(new String(bs), STRING_LEN);
//          */
//         return new StringField(reinterpret_cast<char const*>(arrayOfByte));
//       } catch {
//         // throw new ParseException("cound not parse", 0);
//       }


//     default:
//       break;
//   }

// }
}