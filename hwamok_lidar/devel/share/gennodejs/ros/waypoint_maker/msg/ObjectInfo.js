// Auto-generated. Do not edit!

// (in-package waypoint_maker.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class ObjectInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.objectCounts = null;
      this.centerX = null;
      this.centerY = null;
      this.centerZ = null;
      this.lengthX = null;
      this.lengthY = null;
      this.lengthZ = null;
    }
    else {
      if (initObj.hasOwnProperty('objectCounts')) {
        this.objectCounts = initObj.objectCounts
      }
      else {
        this.objectCounts = 0;
      }
      if (initObj.hasOwnProperty('centerX')) {
        this.centerX = initObj.centerX
      }
      else {
        this.centerX = [];
      }
      if (initObj.hasOwnProperty('centerY')) {
        this.centerY = initObj.centerY
      }
      else {
        this.centerY = [];
      }
      if (initObj.hasOwnProperty('centerZ')) {
        this.centerZ = initObj.centerZ
      }
      else {
        this.centerZ = [];
      }
      if (initObj.hasOwnProperty('lengthX')) {
        this.lengthX = initObj.lengthX
      }
      else {
        this.lengthX = [];
      }
      if (initObj.hasOwnProperty('lengthY')) {
        this.lengthY = initObj.lengthY
      }
      else {
        this.lengthY = [];
      }
      if (initObj.hasOwnProperty('lengthZ')) {
        this.lengthZ = initObj.lengthZ
      }
      else {
        this.lengthZ = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ObjectInfo
    // Serialize message field [objectCounts]
    bufferOffset = _serializer.int32(obj.objectCounts, buffer, bufferOffset);
    // Serialize message field [centerX]
    bufferOffset = _arraySerializer.float64(obj.centerX, buffer, bufferOffset, null);
    // Serialize message field [centerY]
    bufferOffset = _arraySerializer.float64(obj.centerY, buffer, bufferOffset, null);
    // Serialize message field [centerZ]
    bufferOffset = _arraySerializer.float64(obj.centerZ, buffer, bufferOffset, null);
    // Serialize message field [lengthX]
    bufferOffset = _arraySerializer.float64(obj.lengthX, buffer, bufferOffset, null);
    // Serialize message field [lengthY]
    bufferOffset = _arraySerializer.float64(obj.lengthY, buffer, bufferOffset, null);
    // Serialize message field [lengthZ]
    bufferOffset = _arraySerializer.float64(obj.lengthZ, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ObjectInfo
    let len;
    let data = new ObjectInfo(null);
    // Deserialize message field [objectCounts]
    data.objectCounts = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [centerX]
    data.centerX = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [centerY]
    data.centerY = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [centerZ]
    data.centerZ = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [lengthX]
    data.lengthX = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [lengthY]
    data.lengthY = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [lengthZ]
    data.lengthZ = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.centerX.length;
    length += 8 * object.centerY.length;
    length += 8 * object.centerZ.length;
    length += 8 * object.lengthX.length;
    length += 8 * object.lengthY.length;
    length += 8 * object.lengthZ.length;
    return length + 28;
  }

  static datatype() {
    // Returns string type for a message object
    return 'waypoint_maker/ObjectInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5e6aef47c27b53cd5c80f176681e421e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 objectCounts
    float64[] centerX
    float64[] centerY
    float64[] centerZ
    float64[] lengthX
    float64[] lengthY
    float64[] lengthZ
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ObjectInfo(null);
    if (msg.objectCounts !== undefined) {
      resolved.objectCounts = msg.objectCounts;
    }
    else {
      resolved.objectCounts = 0
    }

    if (msg.centerX !== undefined) {
      resolved.centerX = msg.centerX;
    }
    else {
      resolved.centerX = []
    }

    if (msg.centerY !== undefined) {
      resolved.centerY = msg.centerY;
    }
    else {
      resolved.centerY = []
    }

    if (msg.centerZ !== undefined) {
      resolved.centerZ = msg.centerZ;
    }
    else {
      resolved.centerZ = []
    }

    if (msg.lengthX !== undefined) {
      resolved.lengthX = msg.lengthX;
    }
    else {
      resolved.lengthX = []
    }

    if (msg.lengthY !== undefined) {
      resolved.lengthY = msg.lengthY;
    }
    else {
      resolved.lengthY = []
    }

    if (msg.lengthZ !== undefined) {
      resolved.lengthZ = msg.lengthZ;
    }
    else {
      resolved.lengthZ = []
    }

    return resolved;
    }
};

module.exports = ObjectInfo;
