<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
	version="1.0"
	xmlns:func="http://exslt.org/functions"
	xmlns:tst="http://test/namespace"
        extension-element-prefixes="func">
<xsl:output method="text"/>

<func:function name="tst:concatenator">
   <xsl:param name="set"/>

   <func:result>
      <xsl:for-each select="$set">
         <xsl:text>Some other non-constant text: </xsl:text><xsl:value-of select="." /><xsl:text>&#xA;</xsl:text>
      </xsl:for-each>
   </func:result>
</func:function>

<xsl:template match="/">
	<xsl:for-each select="a/b">
		<xsl:text>Some text.&#xA;</xsl:text>
		<xsl:message>Generate some non-constant text <xsl:value-of select="." /></xsl:message>
		<xsl:value-of select="tst:concatenator(.)" />
      </xsl:for-each>
</xsl:template>

</xsl:stylesheet>

