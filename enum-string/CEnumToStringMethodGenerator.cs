namespace EnumStringUtil 
{
    /// <summary>
    /// Generates a method that switchs through the enum type and returns a the type as as a string.
    /// The generated method written to the provided filepath to the given header file path.
    /// </summary>
    public static class CEnumToStringMethodGenerator
    {
        private const string ENUM_VALUE_PLACEHOLDER= "#$value$#";
        private const string ENUM_VALUE_STRING_TEMPLATE = $"{ENUM_VALUE_PLACEHOLDER}";
        private const string ENUM_TYPEDEF_START = "typedef enum TokenKind\r\n{";
        private const string ENUM_TYPEDEF_END = "} TokenKind;";
        private const string ENUM_START_INDICATOR = "@#&";
        private const string ENUM_END_INDICATOR = "!@#&";
        private const string CONVERSION_METHOD_NAME = "tk_to_string";

        private const string ENUM_HEADER_FILEPATH = @"C:\Users\Shariar\Documents\Projects\style-me\style-me\TOKEN_KIND.h";
        private const string ENUM_CONVERSION_HEADER_FILEPATH = @"C:\Users\Shariar\Documents\Projects\style-me\style-me\TK_ENUM_CONVERSION.h";

        public static void Main() 
        {
            try
            {
                string enumToString = GenerateEnumToStringMethod();
                WriteConversionMethodToFile(enumToString);
                Log("Conversion method succesfully written.");
            }
            catch (System.Exception ex)
            {
                Log("Unable to write conversion method.");
                Log(ex.Message);
            }
        }

        private static void WriteConversionMethodToFile(string methodString) 
        {
            if (string.IsNullOrEmpty(methodString)) { return; }
            string headerFilePrepocs = "#pragma once\r\n#include \"TOKEN_KIND.h\"\r\n\n";
            string conversionHeader = headerFilePrepocs + methodString;
            File.WriteAllText(ENUM_CONVERSION_HEADER_FILEPATH, conversionHeader);
        }

        private static string GenerateEnumToStringMethod() 
        {
            string enumDef = ParseEnumDefinition();
            string[] enumValues = enumDef.Split(",");
            if (enumValues == null || enumValues.Length <= 0)
                return null;
            string conversionMethod = $"inline const char* {CONVERSION_METHOD_NAME}(TokenKind kind) \r\n{{\r\n\tswitch (kind)\r\n\t{{\r\n\t\tdefault: return \"UNKNOWN\";";
            foreach (var val in enumValues) 
            {
                string valStringFormat = ENUM_VALUE_STRING_TEMPLATE.Replace(ENUM_VALUE_PLACEHOLDER, val);
                conversionMethod += $"\r\n\t\tcase {val}: return \"{valStringFormat}\";";
            }
            conversionMethod += "\r\n\t}\r\n}";
            return conversionMethod;
        }

        private static string ParseEnumDefinition() 
        {
            string enumHeader = File.ReadAllText(ENUM_HEADER_FILEPATH);
            if (string.IsNullOrEmpty(enumHeader))
                return "Header file has no content";
            enumHeader = enumHeader.Replace(ENUM_TYPEDEF_START, ENUM_START_INDICATOR)
                             .Replace(ENUM_TYPEDEF_END, ENUM_END_INDICATOR)
                             .Replace("\r", "")
                             .Replace("\t", "")
                             .Replace("\n", "");

            int start = enumHeader.IndexOf(ENUM_START_INDICATOR) + ENUM_START_INDICATOR.Length;
            int end = enumHeader.IndexOf(ENUM_END_INDICATOR);
            return enumHeader.Substring(start, end - start);
        }

        private static void Log(object msg) 
        {
            Console.WriteLine(msg);
        }
    }
}
