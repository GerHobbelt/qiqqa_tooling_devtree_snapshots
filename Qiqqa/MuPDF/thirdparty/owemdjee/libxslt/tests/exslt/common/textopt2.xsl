<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
	version="1.0"
	xmlns:exsl="http://exslt.org/common"
	xmlns:tst="http://test/namespace"
        extension-element-prefixes="exsl">
<xsl:output method="text"/>

<xsl:template match="/">
	<xsl:for-each select="a/b">
			<xsl:message>Generate some non-constant text <xsl:value-of select="." /></xsl:message>
		<xsl:variable name="myvar"><node>
			<xsl:text>Some text.&#xA;</xsl:text>
			<xsl:text>Some other non-constant text: </xsl:text><xsl:value-of select="." /><xsl:text>&#xA;</xsl:text>
		</node></xsl:variable>
		<xsl:variable name="myvarnodeset" select="exsl:node-set($myvar)"/>
		<xsl:value-of select="$myvarnodeset/node" />
      </xsl:for-each>
</xsl:template>

</xsl:stylesheet>

