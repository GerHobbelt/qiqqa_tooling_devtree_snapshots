<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
version="1.0">
<xsl:output method="text"/>

<xsl:template match="/">
	<xsl:for-each select="a/b">
		<xsl:text>Some text.</xsl:text>
		<xsl:variable name="some-concat">
			<xsl:text>concat by template(plop </xsl:text>
			<xsl:value-of select="." />
			<xsl:text> plip)</xsl:text>
		</xsl:variable>
		<xsl:text>more text.&#xA;</xsl:text>
		<xsl:variable name="some-func-concat" select="concat('concat by func (plop ', ., ' plip)')" />
		<xsl:text>more text again.&#xA;</xsl:text>
      <xsl:message>Generate some non-constant text <xsl:value-of select="." /></xsl:message>
      <xsl:text>Some other non-constant text: </xsl:text><xsl:value-of select="." /><xsl:text>&#xA;</xsl:text>
      <xsl:value-of select="$some-concat" />
      <xsl:text>:</xsl:text>
      <xsl:value-of select="$some-func-concat" />
      <xsl:text>&#xA;</xsl:text>

      </xsl:for-each>
</xsl:template>

</xsl:stylesheet>

