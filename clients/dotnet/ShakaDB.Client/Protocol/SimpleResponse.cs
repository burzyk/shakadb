﻿namespace ShakaDB.Client.Protocol
{
    using System.IO;

    public class SimpleResponse : BasePacket
    {
        public SimpleResponse(ResponseCode responseCode)
        {
            ResponseCode = responseCode;
        }

        public SimpleResponse(byte[] payload)
            : base(payload)
        {
        }

        public ResponseCode ResponseCode { get; private set; }

        public override PacketType PacketType => PacketType.SimpleResponse;

        protected override void Load(BinaryReader reader)
        {
            ResponseCode = (ResponseCode) reader.ReadByte();
        }

        protected override void Save(BinaryWriter writer)
        {
            writer.Write((byte) ResponseCode);
        }
    }
}